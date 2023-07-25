// avr_blink - uses bit setting by registers instead of digitalWrite()
//   This allows you to use a scope to confirm delay is exactly 1 millisecond
//   or other timing exercises, for example: (when measured)
//   blink 2.0108s period while avr_blink 2.0022s period for a delay of 1000ms
//   or remove the delays and determine fastest blink is 2.02MHz w/ -Og -ggdb
//   or remove the delays and determine fastest blink is 2.68MHz w/ -Os -g

#include <delay.h>
 
int main(void)
{
    /* set pin to output*/
    DDRB |= (_BV(PORTB5));

    while(1) 
    {
        /* turn led on and off */
        PINB |= (_BV(PORTB5));
        _delay_ms(1);
        PORTD &= ~(_BV(PORTD2));
        _delay_ms(1);
    }
    return 0; 
}
