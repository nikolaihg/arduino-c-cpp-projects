#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#define BAUD 9600 // Serial communication speed
#define MYUBRR F_CPU/16/BAUD-1 // UBBR = UART BAUD RATE REGISTER, F_CPU = clock frequency
#define SENSOR_PIN 3 // ADC channel (A3 = 3, A0 = 0, etc.)
#define VCC 5.0 // Supply voltage (change to 3.3V if needed)
#define ADC_MAX 1024.0 // ADC bitrange
#define SAMPLE_DELAY 2500 // Delay between readings (milliseconds)

// ubrr = unsigned baud rate register
void uart_init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Enable RX and TX
    UCSR0C = (1 << USBS0) | (3 << UCSZ00); // 8 databits, 2 stop bits
}

void uart_transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void uart_print(const char* str) {
    while (*str) {
        uart_transmit(*str++);
    }
}

void uart_print_float(float value) {
    char buffer[16];
    dtostrf(value, 0, 1, buffer);
    uart_print(buffer);
}

void adc_init() {
    ADMUX = (1 << REFS0); // Use AVCC (5V) as reference
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, prescaler 128
}

uint16_t adc_read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}

int main() {
    uart_init(MYUBRR);
    adc_init();
   
    while(1) {
        uint16_t adc_value = adc_read(SENSOR_PIN);
        float voltage = adc_value * (VCC / ADC_MAX);
        float temperature = (voltage - 0.5) * 100.0;
       
        uart_print("Temperature: ");
        uart_print_float(temperature);
        uart_print("°C\n");
       
        _delay_ms(SAMPLE_DELAY);
    }
}