#include "unolib.h"

void off_led ()
{
    DDRB |= (_BV(PORTB5));
    PORTB &= ~(_BV(PORTB5));
}

void on_led ()
{
    DDRB |= (_BV(PORTB5));
    PORTB |= (_BV(PORTB5));
}

void tog_led ()
{
    PINB |= (_BV(PORTB5));
}

void set_bit (volatile uint8_t *port, uint8_t bit)
{
*port |= _BV(bit);
}

void clr_bit (volatile uint8_t *port, uint8_t bit)
{
*port &= ~(_BV(bit));
}

void tog_bit (volatile uint8_t *port, uint8_t bit)
{
    *port |= _BV(bit);
}
