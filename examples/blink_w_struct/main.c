// blink without delay using a struct array and an init function

#include "unolib.h"
#include "pinMode.h"
#include "digitalWrite.h"
#include "sysclock.h"

typedef struct blinker
{
  uint8_t ledPin;           // the number of the LED pin
  uint8_t state;          // the state (HIGH/LOW) the LED pin
  uint16_t interval;      // interval at which to blink (milliseconds)
  uint16_t previousMillis;   // will store last time LED was updated
} blinker;

blinker LEDS[3];

struct blinker init(uint8_t ledPin, uint8_t state, uint16_t interval,\
    uint16_t previousMillis)
{
    struct blinker temp;
    temp.ledPin = ledPin;
    temp.state = state;
    temp.interval = interval;
    temp.previousMillis = 0;
    pinMode(temp.ledPin, OUTPUT);
    return temp;
}  

int main (void)
{
    init_sysclock_2 ();
    LEDS[0] = init(3, LOW, 100, 0);
    LEDS[1] = init(5, LOW, 500, 0);
    LEDS[2] = init(6, LOW, 1000, 0);
    while(1)
    {
        uint32_t currentMillis = millis();
        for (uint8_t i = 0; i < 3; i++)
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
