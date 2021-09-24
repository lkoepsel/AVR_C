#include "avr_uno.h"

void off_led ()
{
    // Set the built-in LED PB5 to be an output
    DDRB |= _BV(DDB5);
    PORTB &= ~(_BV(PORTB5));
}

void on_led ()
{
    // Set the built-in LED PB5 to be an output
    DDRB |= _BV(DDB5);
    PORTB |= (_BV(PORTB5));
}

void set_bit (volatile uint8_t *port, uint8_t bit)
{
*port |= _BV(bit);
}

void clr_bit (volatile uint8_t *port, uint8_t bit)
{
*port &= ~(_BV(bit));
}
