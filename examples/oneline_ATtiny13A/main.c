// One line kernal for multitasking
// https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/
// Designed for speed, provides a 200kHz 1/n duty cycle signal
// With three functions, 200kHz 33% duty cycle signal
// With six functions, 103kHz 16% duty cycle signal
#include <avr/io.h>
#include "delay.h"

#define NTASKS 5

// Uno pin numbers
enum {LED0, LED1, LED2, LED3, LED4};
volatile uint8_t MS0=255;
volatile uint8_t MS1=100;
volatile uint8_t MS2=150;
volatile uint8_t MS3=200;
volatile uint8_t MS4=250;


void zero (void) {
    /* toggle led on and off */
    PINB |= _BV(LED0);
    delay(MS0);
    return;
} 

void one (void) {
    /* toggle led on and off */
    PINB |= _BV(LED1);
    delay(MS1);
    return;
} 

void two (void) {
    /* toggle led on and off */
    PINB |= _BV(LED2);
    delay(MS2);
    return;
} 

void three (void) {
    /* toggle led on and off */
    PINB |= _BV(LED3);
    delay(MS3);
    return;
} 

void four (void) {
    /* toggle led on and off */
    PINB |= _BV(LED4);
    delay(MS4);
    return;
} 

void (*tasklist[NTASKS])() = {zero, one, two, three, four};

int main(void)
{
    DDRB |= (_BV(LED0) | _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4));

    while (1)
    {
    for (uint8_t taskcount=0; taskcount < NTASKS; ++taskcount)
        {
            (*tasklist[taskcount])();

        }
    }
    return 0; 
}

