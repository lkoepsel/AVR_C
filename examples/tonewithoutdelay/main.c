// ToneWithoutDelay - demonstrate flash w/o delay using a tone
// Similar to Adafruit tutorial:
// https://learn.adafruit.com/multi-tasking-the-arduino-part-1?view=all

#include "tone.h"

// constants won't change. Used here to 
// set pin number and time interval:
const uint8_t tonePin =  8;        // the number of the LED pin
const uint32_t OnTime = 1000;      // interval On (milliseconds)
const uint32_t OffTime = 2000;     // interval Off (milliseconds)

// Variables will change:
uint8_t toneState = LOW;           // LED State variable, tracks state of LED
uint32_t previousMillis = 0;        // will store last time LED was updated

int main (void)
{
  // Set up a system tick of 1 millisec (1kHz)
  init_sysclock_2 ();

    while(1)
    {
        // check to see if it's time to blink the LED
        uint32_t currentMillis = millis();

        if ((toneState == HIGH) && (currentMillis - previousMillis >= OnTime)) 
        {
        // save the last time you blinked the LED and change state
        previousMillis = currentMillis;   
        toneState = LOW;
        noTone(tonePin);
        }
        if ((toneState == LOW) && (currentMillis - previousMillis >= OffTime)) 
        {
        // save the last time you blinked the LED and change state
        previousMillis = currentMillis;   
        toneState = HIGH;
        tone_on(tonePin, NOTE_C4);
        }
    }
}
