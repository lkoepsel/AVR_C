// One line kernal for multitasking
// https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/
// Designed using pure Arduino-style code, as it tracks state and uses digitalWrite
// Provides a 50% duty cycle signal
// With three functions, 36kHz 50% duty cycle signal

#include "pinMode.h"
#include "digitalWrite.h"

#define NTASKS 3

// Uno pin numbers
#define LED0 4
#define LED1 5
#define LED2 6
uint8_t state0 = LOW;
uint8_t state1 = LOW;
uint8_t state2 = LOW;

void zero (void) {
    /* toggle led on and off */
    state0 = !state0;
    digitalWrite(LED0, state0);
    return;
} 

void one (void) {
    /* toggle led on and off */
    state1 = !state1;
    digitalWrite(LED1, state1);
    return;
} 

void two (void) {
    /* toggle led on and off */
    state2 = !state2;
    digitalWrite(LED2, state2);
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
