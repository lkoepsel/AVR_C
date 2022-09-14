/* One line kernal for multitasking
*  https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/
*  Designed for speed, provides a 200kHz 1/n duty cycle signal
*  With three functions, 200kHz 33% duty cycle signal
*/

#include <avr/io.h>

#define NTASKS 3

// Uno pin numbers
#define LED0 3
#define LED1 5
#define LED2 6

void zero (void) {
    /* toggle led on and off */
    PIND |= _BV(LED0);
    return;
} 

void one (void) {
    /* toggle led on and off */
    PIND |= _BV(LED1);
    return;
} 

void two (void) {
    /* toggle led on and off */
    PIND |= _BV(LED2);
    return;
} 

void (*tasklist[NTASKS])() = {zero, one, two};

int main(void)
{
    DDRD |= (_BV(LED0) | _BV(LED1) | _BV(LED2));

    while (1)
    {
    for (uint8_t taskcount=0; taskcount < NTASKS; ++taskcount)
        {
            (*tasklist[taskcount])();
        }
    }
    return(0); 
}

