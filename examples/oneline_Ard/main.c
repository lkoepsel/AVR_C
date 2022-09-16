/* One line kernal for multitasking
*  https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/
*  Designed using Arduino-style code, provides a 67kHz 1/n duty cycle signal
*  With three functions, 67kHz 33% duty cycle signal
*/

#include "pinMode.h"
#include "digitalWrite.h"

#define NTASKS 3

// Uno pin numbers
#define LED0 3
#define LED1 5
#define LED2 6

void zero (void) {
    /* toggle led on and off */
    digitalWrite(LED0, TOG);
    return;
} 

void one (void) {
    /* toggle led on and off */
    digitalWrite(LED1, TOG);
    return;
} 

void two (void) {
    /* toggle led on and off */
    digitalWrite(LED2, TOG);
    return;
} 

void (*tasklist[NTASKS])() = {zero, one, two};

int main(void)
{
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    while (1)
    {
    for (uint8_t taskcount=0; taskcount < NTASKS; ++taskcount)
        {
            (*tasklist[taskcount])();
        }
    }
    return 0; 
}
