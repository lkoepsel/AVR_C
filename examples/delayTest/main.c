/*
* delayTest()
* Simple timer which toggles pin at 1000Hz or 1ms timer. All at 50% duty cycle.
* Once tested, will be used as a dynamic delay.
*/
#include <avr/io.h>
#include "pinMode.h"
#include "digitalWrite.h"
#include "delay.h"

int main (void)
{
    pinMode(7, OUTPUT);
    /* loop forever, the interrupts are doing the rest */
    while(1)  {
        delay(100);
        digitalWrite(7, TOG);
    }
    return (0);
}
                
