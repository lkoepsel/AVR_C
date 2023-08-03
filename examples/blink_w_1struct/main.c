// blink_w_1struct - blink 1 led without delay using a struct
#include "pinMode.h"
#include "digitalWrite.h"
#include "sysclock.h"

struct blinker
{
  uint8_t ledPin;           // the number of the LED pin
  uint8_t state;          // the state (HIGH/LOW) the LED pin
  uint32_t interval;      // interval at which to blink (milliseconds)
  uint32_t previousMillis;   // will store last time LED was updated
} ;
struct blinker LED;

int main (void)
{
  init_sysclock_2 ();
  LED.ledPin = 4;
  LED.state = LOW;
  LED.interval = 1000;
  LED.previousMillis = 0;
  pinMode(LED.ledPin, OUTPUT);      

    while(1)
    {
        uint32_t currentMillis = millis();
        if(currentMillis - LED.previousMillis > LED.interval) 
        {
            LED.previousMillis = currentMillis;   
            LED.state = !LED.state;
            digitalWrite(LED.ledPin, LED.state);
        }
    }
}
