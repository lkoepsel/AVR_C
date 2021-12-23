/* One line kernal for multitasking
*  https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/
*
*/

#include <avr/io.h>
#include "delay.h"
#include "pinMode.h"
#include "sysclock.h"

#define NTASKS 3

typedef struct task {
   uint8_t pin;             // Uno pin 
   volatile uint8_t *port;  // Port for Uno pin 
   uint8_t bit;             // Bit in Port for pin 
   uint8_t state;           // Is led on or off
   uint16_t on;             // Time led is on
   uint16_t off;            // Time led is off
   uint16_t elapsed;        // Time elapsed sinced last in loop
} task;

task tasks[NTASKS];

// Uno pin numbers
enum {LED0=2, LED1, LED2, LED3, LED4, LED5, LED6, LED8, LED7, LED9};

void update (uint8_t taskID) {
    // Based on adafruit lesson on classes
    // Changed digitalWrite() to bit action, due to overhead of dW()
    uint16_t now = millis();
     
    if((tasks[taskID].state == HIGH) && (now - tasks[taskID].elapsed >= tasks[taskID].on))
    {
        tasks[taskID].state = LOW;  // Turn it off
        tasks[taskID].elapsed = now;  // Remember the time
        // digitalWrite(tasks[taskID].pin, tasks[taskID].state);  // Update the actual LED
        clr_bit(tasks[taskID].port, tasks[taskID].bit);
    }
    else if ((tasks[taskID].state == LOW) && (now - tasks[taskID].elapsed >= tasks[taskID].off))
    {
        tasks[taskID].state = HIGH;  // turn it on
        tasks[taskID].elapsed = now;   // Remember the time
        // digitalWrite(tasks[taskID].pin, tasks[taskID].state);     // Update the actual LED
        set_bit(tasks[taskID].port, tasks[taskID].bit);
    }
    return;
} 

int main(void)
{
    init_sysclock ();

    // struct: {pin, *port, bit, state, on, off, elapsed}
    uint8_t i = 0;
    tasks[i].pin = LED0;
    tasks[i].state = LOW;
    tasks[i].on = 2;
    tasks[i].off = 8;
    tasks[i].elapsed = 0;
    i++;
    tasks[i].pin = LED1;
    tasks[i].state = LOW;
    tasks[i].on = 3;
    tasks[i].off = 2;
    tasks[i].elapsed = 0;
    i++;
    tasks[i].pin = LED2;
    tasks[i].state = LOW;
    tasks[i].on = 8;
    tasks[i].off = 2;
    tasks[i].elapsed = 0;
    i++;

    // Added port and bit to enable using a set_bit or clr_bit, due to overhead of dW()
    for (uint8_t task=0; task < NTASKS; ++task) {
        pinMode(tasks[task].pin, OUTPUT);
        if ((tasks[task].pin >= 0) && (tasks[task].pin <= 7)) {
            tasks[task].port = &PORTD;
            tasks[task].bit = tasks[task].pin;
        }
        else if ((tasks[task].pin >= 8) && (tasks[task].pin <= 15)) {
            tasks[task].port = &PORTB;
            tasks[task].bit = tasks[task].pin - 8;        
        }
    }
    while (1)
    {
    for (uint8_t task=0; task < NTASKS; ++task)
        {
            update(task);
        }
    }
    return(0); 
}
