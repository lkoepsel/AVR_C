/* delayTest()
*   gcc-based delay() for simplicity and is accurate, blocking to meet needs
*   Uses built-in delay_ms for delay, allows for passing a variable
*/
#include <avr/io.h>
#include "pinMode.h"
#include "delay.h"

int main (void)
{
    uint8_t testPin = 2;
    pinMode(testPin, OUTPUT);

    while(1)  {
        // HIGH width is 2000us or 2ms
        PORTD |= _BV(PD2);
        delay(2);

        // LOW width is 4000us or 4ms
        PORTD &= ~(_BV(PD2));
        delay(4);
    }
    return (0);
}
                
