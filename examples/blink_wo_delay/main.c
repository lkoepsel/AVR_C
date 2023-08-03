// Blink without Delay C version
// Based on Arduino tutorial:
// http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
// And the Adafruit tutorial:
// https://learn.adafruit.com/multi-tasking-the-arduino-part-1?view=all

#include "pinMode.h"
#include "digitalWrite.h"
#include "sysclock.h"


// constants won't change. Used here to 
// set pin number and time interval:
const uint8_t ledPin =  4;          // the number of the LED pin
const uint32_t interval = 1000;     // interval at which to blink (milliseconds)

// Variables will change:
uint32_t previousMillis = 0;        // will store last time LED was updated

int main (void)
{
  // Set up a system tick of 1 millisec (1kHz)
  init_sysclock_2 ();

  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);      

    while(1)
    {
        // check to see if it's time to blink the LED; that is, if the 
        // difference between the current time and last time you blinked 
        // the LED is bigger than the interval at which you want to 
        // blink the LED.
        uint32_t currentMillis = millis();

        if(currentMillis - previousMillis > interval) {
        // save the last time you blinked the LED 
        previousMillis = currentMillis;   
        // toggle the state of the LED
        digitalWrite(ledPin, TOG);
        }
    }
}
