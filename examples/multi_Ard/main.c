/* One line kernal for multitasking
*  https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/
*  Uses Arduino-style digitalWrite()
*  Overhead from dw delivers 22kHz signal from 10 tasks
*/

#include <avr/io.h>
#include "pinMode.h"
#include "digitalWrite.h"

#define NTASKS 8

#define LED0  2 
#define LED1  3
#define LED2  4
#define LED3  5
#define LED4  6
#define LED5  7
#define LED6  8
#define LED7  9

struct task {
   void (*TickFct)();    // Function to call for task's tick
} task;

struct task tasks[NTASKS];

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

void three (void) {
    /* toggle led on and off */
    digitalWrite(LED3, TOG);
    return;
} 

void four (void) {
    /* toggle led on and off */
    digitalWrite(LED4, TOG);
    return;
} 

void five (void) {
    /* toggle led on and off */
    digitalWrite(LED5, TOG);
    return;
} 

void six (void) {
    /* toggle led on and off */
    digitalWrite(LED6, TOG);
    return;
} 

void seven (void) {
    /* toggle led on and off */
    digitalWrite(LED7, TOG);
    return;
} 

// void eight (void) {
//     /* toggle led on and off */
//     digitalWrite(LED8, TOG);
//     return;
// } 

// void nine (void) {
//     /* toggle led on and off */
//     digitalWrite(LED9, TOG);
//     return;
// } 

int main(void)
{
    for (uint8_t i=0;i<NTASKS;i++) {
        pinMode(i, OUTPUT);
    }

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
   // ++i;
   // tasks[i].TickFct = &eight;
   // ++i;
   // tasks[i].TickFct = &nine;

    while (1)
    {
    for (uint8_t taskcount=0; taskcount < NTASKS; ++taskcount)
        {
            tasks[taskcount].TickFct();
        }
    }
    return 0; 
}

