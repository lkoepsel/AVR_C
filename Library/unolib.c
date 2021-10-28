#include "unolib.h"

// #define INPUT 0
// #define OUTPUT 1
// #define INPUT_PULLUP 2
// #define TOG 3
// #define HIGH 1
// #define LOW 0

// #define A0 0
// #define A1 1
// #define A2 2
// #define A3 3
// #define A4 4
// #define A5 5

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
