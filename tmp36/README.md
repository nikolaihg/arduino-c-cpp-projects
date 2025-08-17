# TMP36 Temperature Reader
A bare-metal AVR C++ program to read temperature from a TMP36 sensor and output via UART serial communication.

## Connections:
- TMP36 $V_s$ (left pin) → $5V$ power supply
- TMP36 $V_{out}$ (middle pin) → Arduino $A3$ (ADC channel 3)
- TMP36 $GND$ (right pin) → $GND$


## Registers Used
###  UART Registers
- UBRR0H/UBRR0L - UART Baud Rate Registers (set communication speed)
- UCSR0B - UART Control/Status Register B (enable TX/RX)
- UCSR0C - UART Control/Status Register C (data format: 8 bits, 2 stop bits)
- UCSR0A - UART Control/Status Register A (check if ready to transmit)
- UDR0 - UART Data Register (actual data transmission)

### ADC Registers
- ADMUX - ADC Multiplexer Selection (reference voltage + channel selection)
- ADCSRA - ADC Control/Status Register A (enable ADC + prescaler settings)
- ADC - ADC Data Register (contains conversion result)


**TMP36 Datasheet** - [Analog Devices TMP36](https://www.analog.com/media/en/technical-documentation/data-sheets/TMP35_36_37.pdf)
**ATmega328P Datasheet** - [Microchip ATmega328P](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
