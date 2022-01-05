/* One line kernal for multitasking
*  https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/
*  Uses direct pin manipulation using a set bit on Input Port
*  Delivers 62kHz signal from 10 tasks
*/

#include <avr/io.h>
#include "delay.h"

#define NTASKS 10

// Uno pin numbers
#define LED0 2 
#define LED1 3
#define LED2 4
#define LED3 5
#define LED4 6
#define LED5 7
#define LED6 0
#define LED7 1
#define LED8 2
#define LED9 3

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

void three (void) {
    /* toggle led on and off */
    PIND |= _BV(LED3);
    return;
} 

void four (void) {
    /* toggle led on and off */
    PIND |= _BV(LED4);
    return;
} 

void five (void) {
    /* toggle led on and off */
    PIND |= _BV(LED5);
    return;
} 

void six (void) {
    /* toggle led on and off */
    PINB |= _BV(LED6);
    return;
} 

void seven (void) {
    /* toggle led on and off */
    PINB |= _BV(LED7);
    return;
} 

void eight (void) {
    /* toggle led on and off */
    PINB |= _BV(LED8);
    return;
} 

void nine (void) {
    /* toggle led on and off */
    PINB |= _BV(LED9);
    return;
} 

int main(void)
{
    DDRD |= _BV(LED0) | _BV(LED1) | _BV(LED2)  | _BV(LED3) | _BV(LED4) | _BV(LED5);
    DDRB |= _BV(LED6) | _BV(LED7) | _BV(LED8)  | _BV(LED9);

   uint8_t i = 0;
   tasks[i].TickFct = &zero;
   ++i;
   tasks[i].TickFct = &one;
   ++i;
   tasks[i].TickFct = &two;
   ++i;
   tasks[i].TickFct = &three;
   ++i;
   tasks[i].TickFct = &four;
   ++i;
   tasks[i].TickFct = &five;
   ++i;
   tasks[i].TickFct = &six;
   ++i;
   tasks[i].TickFct = &seven;
   ++i;
   tasks[i].TickFct = &eight;
   ++i;
   tasks[i].TickFct = &nine;

    while (1)
    {
    for (uint8_t taskcount=0; taskcount < NTASKS; ++taskcount)
        {
            tasks[taskcount].TickFct();
            // delay(100);
        }
    }
    return(0); 
}

