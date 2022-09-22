// multi-struct a C compatible version of the Adafruit classy example
// https://learn.adafruit.com/multi-tasking-the-arduino-part-1?view=all
// Uses the "One line kernal for multitasking"
// https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/
// Tasks are individually setup using a struct
// Fundamental task is an on/off signal, whether LED, or speaker

#include <avr/io.h>
#include "delay.h"
#include "pinMode.h"
#include "sysclock.h"
#include "digitalWrite.h"

// Defaults:
//  NTASKS: Number of tasks to be defined
//  DEFAULT_ON/DEFAULT_OFF: Default times (msec) for task to be on/off
//  With On/Off set to 1, three tasks run at 500Hz
#define NTASKS 3
#define DEFAULT_ON 100
#define DEFAULT_OFF 100

// struct task replaces class flasher in Adafruit example
// struct contains the specific variables required to maintain pin, state and time
typedef struct task {
   volatile uint8_t pin;    // Uno pin 
   uint8_t state;           // Is pin HIGH or LOW
   uint16_t on;             // Time on
   uint16_t off;            // Time off
   uint16_t elapsed;        // Time elapsed sinced last in loop
} task;

// now setup an array of structs to easily manage them, we can reference each struct
// by a subscript just like an array
task tasks[NTASKS];

// update is similar to example in that it checks the time and changes state
// if the time has expired, it tracks both on-time and off-time
void update (uint8_t taskID) {
    // Based on adafruit lesson on classes
    uint16_t now = millis();

    if((tasks[taskID].state == HIGH) && (now - tasks[taskID].elapsed >= tasks[taskID].on))
    {
        tasks[taskID].state = LOW;  // Turn it off
        tasks[taskID].elapsed = now;  // Remember the time
        digitalWrite(tasks[taskID].pin, LOW);
    }
    else if ((tasks[taskID].state == LOW) && (now - tasks[taskID].elapsed >= tasks[taskID].off))
    {
        tasks[taskID].state = HIGH;  // turn it on
        tasks[taskID].elapsed = now;   // Remember the time
        digitalWrite(tasks[taskID].pin, HIGH);
    }
    return;
} 

int main(void)
{
    init_sysclock_2 ();

    // think of this section as the Adafruit example "constructor", it initializes the structs
    // struct: {pin, state, on, off, elapsed}
    uint8_t i = 0;
    tasks[i].pin = 3;
    tasks[i].state = LOW;
    tasks[i].on = DEFAULT_ON;
    tasks[i].off = DEFAULT_OFF;
    tasks[i].elapsed = 0;
    i++;
    tasks[i].pin = 5;
    tasks[i].state = LOW;
    tasks[i].on = DEFAULT_ON << 1;
    tasks[i].off = DEFAULT_OFF << 1;
    tasks[i].elapsed = 0;
    i++;
    tasks[i].pin = 6;
    tasks[i].state = LOW;
    tasks[i].on = DEFAULT_ON << 2;
    tasks[i].off = DEFAULT_OFF << 2;
    tasks[i].elapsed = 0;

    // Initializes pin of each task to be an OUTPUT
    for (uint8_t task_cntr=0; task_cntr < NTASKS; ++task_cntr) {
        pinMode(tasks[task_cntr].pin, OUTPUT);
    }
    while (1)
    {
    // same as the Adafruit example, update is very simple
    // in this case, we simply increment through our array of structs
    for (uint8_t task_cntr=0; task_cntr < NTASKS; ++task_cntr)
        {
            update(task_cntr);
        }
    }
    return 0; 
}
