// multi-struct a C compatible version of the Adafruit Classy example
// https://learn.adafruit.com/multi-tasking-the-arduino-part-1?view=all
// Uses the "One line kernal for multitasking"
// https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/
// Tasks are individually setup using a struct

#include <avr/io.h>
#include "delay.h"
#include "pinMode.h"
#include "sysclock.h"
#include "digitalWrite.h"

// Defaults:
//  Nflashers: Number of flashers to be defined
//  DEFAULT_ON/DEFAULT_OFF: Default times (msec) for flasher to be on/off
//  With On/Off set to 1, three tasks run at 500Hz
#define Nflashers 3
#define DEFAULT_ON 100
#define DEFAULT_OFF 100

// struct flasher replaces class flasher in Adafruit example
// struct contains the variables required to maintain pin, state and time
typedef struct flasher 
{
   volatile uint8_t pin;    // Uno pin 
   uint8_t state;           // Is pin HIGH or LOW
   uint16_t on;             // Time on
   uint16_t off;            // Time off
   uint16_t elapsed;        // Time elapsed sinced last in loop
} flasher;

// now setup an array of structs to easily manage them, we can 
// reference each struct by a subscript just like an array
flasher flashers[Nflashers];

// init is similar to the Flasher Constructor in the example
// and initializes the member variables and state, and sets LED pin to OUTPUT
struct flasher init(uint8_t pin, uint8_t state, uint16_t on, uint16_t off,\
        uint16_t elapsed)
{
    struct flasher temp;
    temp.pin = pin;
    temp.state = state;
    temp.on = on;
    temp.off = off;
    temp.elapsed = elapsed;

    pinMode(pin, OUTPUT);
    return temp;
}

// update is similar to Classy update in that it checks the time and changes
// state if the time has expired, it also tracks both on-time and off-time
void update (uint8_t flasherID) 
{
    // Based on adafruit lesson on classes
    uint16_t now = millis();

    if((flashers[flasherID].state == HIGH) &&\
        (now - flashers[flasherID].elapsed >= flashers[flasherID].on))
    {
        flashers[flasherID].state = LOW;  // Turn it off
        flashers[flasherID].elapsed = now;  // Remember the time
        digitalWrite(flashers[flasherID].pin, LOW);
    }
    else if ((flashers[flasherID].state == LOW) &&\
        (now - flashers[flasherID].elapsed >= flashers[flasherID].off))
    {
        flashers[flasherID].state = HIGH;  // turn it on
        flashers[flasherID].elapsed = now;   // Remember the time
        digitalWrite(flashers[flasherID].pin, HIGH);
    }
    return;
}

int main(void)
{
    init_sysclock_2 ();

    // initialize each flasher (struct: {pin, state, on, off, elapsed})
    // in comparison to Classy example, each LED only requires 1 line of code :)
    // AND update Nflashers to number of flashers
    flashers[0] = init(3, LOW, DEFAULT_ON, DEFAULT_OFF, 0);
    flashers[1] = init(5, LOW, DEFAULT_ON << 1, DEFAULT_OFF << 1, 0);
    flashers[2] = init(6, LOW, DEFAULT_ON << 2, DEFAULT_OFF << 2, 0);

    // same as the Adafruit example, update is very simple
    // in this case, we simply increment through our array of structs
    while (1)
    {
    for (uint8_t flasher_cntr=0; flasher_cntr < Nflashers; ++flasher_cntr)
        {
            update(flasher_cntr);
        }
    }
    return 0; 
}
