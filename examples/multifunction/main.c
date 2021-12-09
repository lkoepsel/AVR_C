/* One line kernal for multitasking
*  https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/
*
*/

#include <avr/io.h>

#define NTASKS 3

// Uno pin numbers
#define LED0 3 
#define LED1 5
#define LED2 6

typedef struct task {
   void (*TickFct)();    // Function to call for task's tick
} task;

task tasks[NTASKS];

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

int main(void)
{
    DDRD |= _BV(LED0) | _BV(LED1) | _BV(LED2);

   uint8_t i = 0;
   tasks[i].TickFct = &zero;
   ++i;
   tasks[i].TickFct = &one;
   ++i;
   tasks[i].TickFct = &two;

    while (1)
    {
    for (uint8_t taskcount=0; taskcount < NTASKS; ++taskcount)
        {
            tasks[taskcount].TickFct();
        }
    }
    return(0); 
}

