/* One line kernal for multitasking
*  https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/
*  Tasks are individually setup using a struct
*  Fundamental premise is an on/off signal, whether LED, or speaker
*/

#include <avr/io.h>
#include "delay.h"
#include "pinMode.h"
#include "sysclock.h"
#include "digitalWrite.h"

/* Defaults:
*  NTASKS: Number of tasks to be defined
*  DEFAULT_ON/DEFAULT_OFF: Times for LEDs to be on/off
*  With On/Off set to 1, three tasks run at 500Hz
*/
#define NTASKS 3
#define DEFAULT_ON 100
#define DEFAULT_OFF 100

typedef struct task {
   volatile uint8_t pin;    // Uno pin 
   uint8_t state;           // Is led on or off
   uint16_t on;             // Time led is on
   uint16_t off;            // Time led is off
   uint16_t elapsed;        // Time elapsed sinced last in loop
} task;

task tasks[NTASKS];

// Uno pin numbers
enum {LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11};

void update (uint8_t taskID) {
    // Based on adafruit lesson on classes
    // Changed digitalWrite() to bit action, due to overhead of dW()
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

    // struct: {pin, *port, bit, state, on, off, elapsed}
    uint8_t i = 0;
    tasks[i].pin = LED4;
    tasks[i].state = LOW;
    tasks[i].on = DEFAULT_ON;
    tasks[i].off = DEFAULT_OFF;
    tasks[i].elapsed = 0;
    i++;
    tasks[i].pin = LED6;
    tasks[i].state = LOW;
    tasks[i].on = (DEFAULT_ON << 1);
    tasks[i].off = (DEFAULT_OFF << 1);
    tasks[i].elapsed = 0;
    i++;
    tasks[i].pin = LED7;
    tasks[i].state = LOW;
    tasks[i].on = (DEFAULT_ON << 2);
    tasks[i].off = (DEFAULT_OFF << 2);
    tasks[i].elapsed = 0;

    // Added port and bit to enable using a set_bit or clr_bit, due to overhead of dW()
    for (uint8_t task_cntr=0; task_cntr < NTASKS; ++task_cntr) {
        pinMode(tasks[task_cntr].pin, OUTPUT);
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
