#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 100

int main() {
    /*
    DDRB = Data Direction Register for Port B
    PB5 = Pin B5 (corresponds to pin 13 on the arduino uno)
    Setting bit 5 high makes PB5 an output pin
    Set pin 13 (PB5) as output for onboard LED
    */
    // 
    DDRB |= (1 << PB5);

    while(1) {
        /*
        PORTB = Port B Data Register
        Setting bit 5 high outputs 5V on PB5
        */
        PORTB |= (1 << PB5);
        _delay_ms(BLINK_DELAY_MS);

        /*
        Using bitwise AND with NOT to clear bit 5
        ~(1 << PB5) creates a mask: 11110111*/
        PORTB &= ~(1 << PB5);
        _delay_ms(BLINK_DELAY_MS);
    }

    return 0;
}   