/* blink
*   example of low level code for blinking on-board LED
*/
#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
    // set data direction register (PinMode())
    DDRB |= _BV(DDD5);

    while(1)  {
        // toggle pin by writing a 1 to input register (see page 85 14.2.2)
        // digitalWrite(pin, TOG)
        PINB |= _BV(PORTB5);

        // delay using avr-libc delay macro
        // delay()
        _delay_ms(500);
    }
    return (0);
}
