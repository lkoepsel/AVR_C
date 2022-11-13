// One line kernal for multitasking
// https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/
// Designed for speed, provides a 200kHz 1/n duty cycle signal
// With three functions, 200kHz 33% duty cycle signal
// With six functions, 103kHz 16% duty cycle signal
#include <avr/io.h>

#define NTASKS 6

// Uno pin numbers
enum {LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11};

void zero (void) {
    /* toggle led on and off */
    PIND |= _BV(LED1);
    return;
} 

void one (void) {
    /* toggle led on and off */
    PIND |= _BV(LED2);
    return;
} 

void two (void) {
    /* toggle led on and off */
    PIND |= _BV(LED3);
    return;
} 

void three (void) {
    /* toggle led on and off */
    PIND |= _BV(LED4);
    return;
} 

void four (void) {
    /* toggle led on and off */
    PIND |= _BV(LED5);
    return;
} 

void five (void) {
    /* toggle led on and off */
    PIND |= _BV(LED6);
    return;
} 

void (*tasklist[NTASKS])() = {zero, one, two, three, four, five};

int main(void)
{
    DDRD |= (_BV(LED0) | _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4) | _BV(LED5));

    while (1)
    {
    for (uint8_t taskcount=0; taskcount < NTASKS; ++taskcount)
        {
            (*tasklist[taskcount])();
        }
    }
    return 0; 
}

