/* delayTest()
*   gcc-based delay() for simplicity and is accurate, blocking to meet needs
*   Uses built-in delay_ms for delay, allows for passing a variable
*/
#include <avr/io.h>
#include "pinMode.h"
#include "delay.h"

int main (void)
{
    DDRB |= _BV(DDD5);

    while(1)  {
        // HIGH width is 2000us or 2ms
        PORTB ^= _BV(PORTB5);
        delay(500);
    }
    return (0);
}
                
