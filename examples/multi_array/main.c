/* One line kernal for multitasking
*  https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/
*  Uses Arduino digitalWrite() and adds an array approach
*  each task is identical and in an array
*  Overhead from dw and speed up from array delivers 27kHz signal from 10 tasks
*/

#include <avr/io.h>
#include "delay.h"
#include "pinMode.h"
#include "digitalWrite.h"

#define NTASKS 10

// Uno pin numbers
enum {LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11};

void toggle (uint8_t pin) {
    /* toggle led on and off */
    digitalWrite(pin, TOG);
    return;
} 

int main(void)
{
    for (uint8_t i=0;i<NTASKS;i++) {
        pinMode(i, OUTPUT);
    }

    while (1)
    {
    for (uint8_t pin=0; pin < NTASKS; ++pin)
        {
            toggle(pin);
        }
    }
    return(0); 
}
