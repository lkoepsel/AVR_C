// blink without delay using a struct array
#include "pinMode.h"
#include "digitalWrite.h"
#include "sysclock.h"
#define N_LEDS 3
struct blinker
{
  uint8_t ledPin;           // the number of the LED pin
  uint8_t state;          // the state (HIGH/LOW) the LED pin
  uint32_t interval;      // interval at which to blink (milliseconds)
  uint32_t previousMillis;   // will store last time LED was updated
} ;

struct blinker LEDS[N_LEDS];

int main (void)
{
  // Set up a system tick of 1 millisec (1kHz)
  init_sysclock_2 ();
  LEDS[0].ledPin = 4;
  LEDS[0].state = LOW;
  LEDS[0].interval = 100;
  LEDS[0].previousMillis = 0;

  LEDS[1].ledPin = 5;
  LEDS[1].state = LOW;
  LEDS[1].interval = 500;
  LEDS[1].previousMillis = 0;

  LEDS[2].ledPin = 6;
  LEDS[2].state = LOW;
  LEDS[2].interval = 1000;
  LEDS[2].previousMillis = 0;

  pinMode(LEDS[0].ledPin, OUTPUT);      
  pinMode(LEDS[1].ledPin, OUTPUT);      
  pinMode(LEDS[2].ledPin, OUTPUT);      

    while(1)
    {
        uint32_t currentMillis = millis();
        for (uint8_t i = 0; i < N_LEDS; i++)
        {
            if(currentMillis - LEDS[i].previousMillis > LEDS[i].interval) 
            {
                LEDS[i].previousMillis = currentMillis;   
                LEDS[i].state = !LEDS[i].state;
                digitalWrite(LEDS[i].ledPin, LEDS[i].state);
            }
        }
    }
}
