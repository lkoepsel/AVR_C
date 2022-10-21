// Pulse servo code

#include "pinMode.h"
#include "digitalWrite.h"
#include "sysclock.h"
#include "delay.h"

// constants won't change. Used here to 
// set pin number and time interval:
const uint8_t pulsePIN =  4;          // the number of the LED pin
const uint16_t freq_width = 1000;     // interval at which to blink (milliseconds)

volatile uint8_t pulse_HI_width = 150;
volatile uint8_t pulseState = LOW;
volatile uint16_t clock_width;

int main (void)
{
  // Set up a system tick of 1 millisec (1kHz)
  init_pulse_0 ();
  pinMode(pulsePIN, OUTPUT);      
  clock_width = freq_width - pulse_HI_width;

    while(1)
    {
        delay(10);
    }
}
