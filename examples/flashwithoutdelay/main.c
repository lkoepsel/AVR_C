// FlashWithoutDelay
// Adafruit tutorial:
// https://learn.adafruit.com/multi-tasking-the-arduino-part-1?view=all

#include "pinMode.h"
#include "digitalWrite.h"
#include "sysclock.h"

// constants won't change. Used here to 
// set pin number and time interval:
const uint8_t ledPin =  13;        // the number of the LED pin
const uint32_t OnTime = 250;      // interval On (milliseconds)
const uint32_t OffTime = 750;     // interval Off (milliseconds)

// Variables will change:
uint8_t ledState = LOW;           // LED State variable, tracks state of LED
uint32_t previousMillis = 0;        // will store last time LED was updated

int main (void)
{
  // Set up a system tick of 1 millisec (1kHz)
  init_sysclock_2 ();

  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);      

    while(1)
    {
        // check to see if it's time to blink the LED
        uint32_t currentMillis = millis();

        if ((ledState == HIGH) && (currentMillis - previousMillis >= OnTime)) 
        {
        // save the last time you blinked the LED and change state
        previousMillis = currentMillis;   
        ledState = LOW;
        digitalWrite(ledPin, ledState);
        }
        if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime)) 
        {
        // save the last time you blinked the LED and change state
        previousMillis = currentMillis;   
        ledState = HIGH;
        digitalWrite(ledPin, ledState);
        }
    }
}
