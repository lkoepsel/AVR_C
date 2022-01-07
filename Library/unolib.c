#include "unolib.h"

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
