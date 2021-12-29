/* One line kernal for multitasking
*  https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/
*
*/

#include <avr/io.h>
#include "delay.h"
#include "pinMode.h"
#include "sysclock.h"

#define NTASKS 4
#define default_on 4000
#define default_off 4000

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
enum {LED2=2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11};

void update (uint8_t taskID) {
    // Based on adafruit lesson on classes
    // Changed digitalWrite() to bit action, due to overhead of dW()
    uint16_t now = millis();
     
    if((tasks[taskID].state == HIGH) && (now - tasks[taskID].elapsed >= tasks[taskID].on))
    {
        tasks[taskID].state = LOW;  // Turn it off
        tasks[taskID].elapsed = now;  // Remember the time
        clr_bit(tasks[taskID].port, tasks[taskID].bit);
    }
    else if ((tasks[taskID].state == LOW) && (now - tasks[taskID].elapsed >= tasks[taskID].off))
    {
        tasks[taskID].state = HIGH;  // turn it on
        tasks[taskID].elapsed = now;   // Remember the time
        set_bit(tasks[taskID].port, tasks[taskID].bit);
    }
    return;
} 

int main(void)
{
    init_sysclock ();

    // struct: {pin, *port, bit, state, on, off, elapsed}
    uint8_t i = 0;
    tasks[i].pin = LED2;
    tasks[i].state = LOW;
    tasks[i].on = default_on * i;
    tasks[i].off = default_on * i;
    tasks[i].elapsed = 0;
    i++;
    tasks[i].pin = LED3;
    tasks[i].state = LOW;
    tasks[i].on = default_on * i;
    tasks[i].off = default_on * i;
    tasks[i].elapsed = 0;
    i++;
    tasks[i].pin = LED4;
    tasks[i].state = LOW;
    tasks[i].on = default_on * i;
    tasks[i].off = default_on * i;
    tasks[i].elapsed = 0;
    i++;
    tasks[i].pin = LED5;
    tasks[i].state = LOW;
    tasks[i].on = default_on * i;
    tasks[i].off = default_on * i;
    tasks[i].elapsed = 0;

    // Added port and bit to enable using a set_bit or clr_bit, due to overhead of dW()
    for (uint8_t task_cntr=0; task_cntr < NTASKS; ++task_cntr) {
        pinMode(tasks[task_cntr].pin, OUTPUT);
        if ((tasks[task_cntr].pin >= 0) && (tasks[task_cntr].pin <= 7)) {
            tasks[task_cntr].port = &PORTD;
            tasks[task_cntr].bit = tasks[task_cntr].pin;
        }
        else if ((tasks[task_cntr].pin >= 8) && (tasks[task_cntr].pin <= 15)) {
            tasks[task_cntr].port = &PORTB;
            tasks[task_cntr].bit = tasks[task_cntr].pin - 8;        
        }
    }
    while (1)
    {
    for (uint8_t task_cntr=0; task_cntr < NTASKS; ++task_cntr)
        {
            update(task_cntr);
        }
    }
    return(0); 
}
