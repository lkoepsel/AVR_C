/* avr_blink - uses bit setting by registers instead of digitalWrite()
*   This allows you to use a scope to confirm delay is exactly 1 millisecond
*   or other timing exercises, for example: (when measured)
*   blink 2.0108 ms period while avr_blink 2.0026 ms period
*/
#include <delay.h>
 
int main(void)
{
    /* set pin to output*/
    DDRB |= (_BV(PORTB5));

    while(1) 
    {
        /* toggle led on and off */
        PORTB |= (_BV(PORTB5));
        _delay_ms(100);
        PORTB &= ~(_BV(PORTB5));
        _delay_ms(100);
    }
    return(0); 
}
