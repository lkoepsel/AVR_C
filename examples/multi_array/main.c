/* One line kernal for multitasking
*  https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/
*
*/

#include <avr/io.h>
#include "delay.h"
#include "pinMode.h"
#include "digitalWrite.h"

#define NTASKS 10

// Uno pin numbers
enum {LED0=2, LED1, LED2, LED3, LED4, LED5, LED6, LED8, LED7, LED9};

void toggle (uint8_t pin) {
    /* toggle led on and off */
    digitalWrite(pin, TOG);
    return;
} 

int main(void)
{
    for (int i=2;i<12;i++) {
        pinMode(i, OUTPUT);
    }

    while (1)
    {
    for (uint8_t pin=2; pin < NTASKS + 2; ++pin)
        {
            toggle(pin);
        }
    }
    return(0); 
}
