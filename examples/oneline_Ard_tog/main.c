// One line kernal for multitasking
// https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/
// Designed using hybrid Arduino-style code, as it TOGgles using digitalWrite
// Provides a 1/n duty cycle signal
// With three functions, 72kHz 33% duty cycle signal


#include "pinMode.h"
#include "digitalWrite.h"

#define NTASKS 3

// Uno pin numbers
#define LED0 3
#define LED1 4
#define LED2 5
#define LED3 6

void zero (void) {
    /* TOGgle led on and off */
    digitalWrite(LED0, TOG);
    return;
} 

void one (void) {
    /* TOGgle led on and off */
    digitalWrite(LED1, TOG);
    return;
} 

void two (void) {
    /* TOGgle led on and off */
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
