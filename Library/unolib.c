#include "unolib.h"

// https://www.nongnu.org/avr-libc/user-manual/FAQ.html#faq_softreset 
// Function Implementation
void wdt_init(void)
{
MCUSR = 0;
wdt_disable();
return;
}

void LED_off ()
{
    DDRB |= (_BV(PORTB5));
    PORTB &= ~(_BV(PORTB5));
}

void LED_on ()
{
    DDRB |= (_BV(PORTB5));
    PORTB |= (_BV(PORTB5));
}

// TODO: needs to be tested, caused a reset w/ buttons example
void LED_tog ()
{
    DDRB |= (_BV(PORTB5));
    PINB |= (_BV(PORTB5));
}
