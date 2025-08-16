#include <avr/io.h>
#include <util/delay.h>

int main() {
    // Set pin 13 (PB5) as output for onboard LED
    DDRB |= (1 << PB5);

    while(1) {
        // Turn on LED
        PORTB |= (1 << PB5);
        _delay_ms(1000);

        // Turn LED off
        PORTB &= ~(1 << PB5);
        _delay_ms(1000);
    }

    return 0;
}