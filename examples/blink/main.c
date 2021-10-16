/* blink()
*   Uses only avr-gcc macros and ATmega328P code for blinking the built-in LED
*/
#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
    DDRB |= _BV(DDD5);

    while(1)  {
        // toggle LED using XOR
        PINB |= _BV(PORTB5);
        _delay_ms(500);
    }
    return (0);
}
