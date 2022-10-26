// blink without delay using a struct array then add an init function
// the init function will simplify adding additional LEDs
#include "pinMode.h"
#include "digitalWrite.h"
#include "sysclock.h"

#define N_LEDS 3
struct blinker
{
  uint8_t ledPin;           // the number of the LED pin
  uint8_t state;            // the state (HIGH/LOW) the LED pin
  uint16_t interval;        // interval at which to blink (milliseconds)
  uint16_t previousMillis;  // will store last time LED was updated
} ;
struct blinker LEDS[N_LEDS];

void init(uint8_t index, uint8_t ledPin, uint8_t state, uint16_t interval,\
    uint16_t previousMillis)
{
    LEDS[index].ledPin = ledPin;
    LEDS[index].state = state;
    LEDS[index].interval = interval;
    LEDS[index].previousMillis = 0;
    pinMode(LEDS[index].ledPin, OUTPUT);
    return ;
}  

int main (void)
{
    init_sysclock_2 ();
    // Parameters: index, pin, state, interval, previous
    init(0, 3, LOW, 125, 0);
    init(1, 5, LOW, 250, 0);
    init(2, 6, LOW, 375, 0);

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
