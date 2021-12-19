/* One line kernal for multitasking
*  https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/
*
*/

#include <avr/io.h>
#include "delay.h"
#include "pinMode.h"
#include "digitalWrite.h"
#include "sysclock.h"

#define NTASKS 3

typedef struct task {
   uint8_t pin;             // Uno pin number
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
    uint16_t now = millis();
     
    if((tasks[taskID].state == HIGH) && (now - tasks[taskID].elapsed >= tasks[taskID].on))
    {
        tasks[taskID].state = LOW;  // Turn it off
        tasks[taskID].elapsed = now;  // Remember the time
        digitalWrite(tasks[taskID].pin, tasks[taskID].state);  // Update the actual LED
    }
    else if ((tasks[taskID].state == LOW) && (now - tasks[taskID].elapsed >= tasks[taskID].off))
    {
        tasks[taskID].state = HIGH;  // turn it on
        tasks[taskID].elapsed = now;   // Remember the time
        digitalWrite(tasks[taskID].pin, tasks[taskID].state);     // Update the actual LED
    }
    return;
} 

int main(void)
{
    init_sysclock ();

    uint8_t i = 0;
    tasks[i].pin = LED0;
    tasks[i].state = LOW;
    tasks[i].on = 40;
    tasks[i].off = 40;
    tasks[i].elapsed = 0;
    i++;
    tasks[i].pin = LED1;
    tasks[i].state = LOW;
    tasks[i].on = 30;
    tasks[i].off = 20;
    tasks[i].elapsed = 0;
    i++;
    tasks[i].pin = LED2;
    tasks[i].state = LOW;
    tasks[i].on = 80;
    tasks[i].off = 20;
    tasks[i].elapsed = 0;
    i++;

    for (uint8_t task=0; task < NTASKS; ++task) {
        pinMode(tasks[i].pin, OUTPUT);
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
