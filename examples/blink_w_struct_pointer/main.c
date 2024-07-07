// blink without delay using a struct w/pointer instead of struct w/array
// it demonstrates how to reference using a pointer instead of indexing an array
// the init function will simplify adding additional LEDs
#include "pinMode.h"
#include "digitalWrite.h"
#include "sysclock.h"

#define N_LEDS 3
struct blinker
{
  uint8_t ledPin;           // the number of the LED pin
  uint8_t state;            // the state (HIGH/LOW) the LED pin
  uint32_t interval;        // interval at which to blink (milliseconds)
  uint32_t previousMillis;  // will store last time LED was updated
} ;

struct blinker LEDS[N_LEDS];
struct blinker *p_LED;

void init(uint8_t ledPin, uint8_t state, uint32_t interval,\
    uint32_t previousMillis)
{
    p_LED->ledPin = ledPin;
    p_LED->state = state;
    p_LED->interval = interval;
    p_LED->previousMillis = 0;
    pinMode(p_LED->ledPin, OUTPUT);
    p_LED++;
    return ;
}  

void update(struct blinker *p)
{
   uint32_t currentMillis = millis();
   if(currentMillis - p->previousMillis > p->interval)
   {
       p->previousMillis = currentMillis;
       p->state = !p->state;
       digitalWrite(p->ledPin, p->state);
   }
}

int main (void)
{
    init_sysclock_2 ();
    p_LED = LEDS;
    // Parameters: pin, state, interval, previous
    init(13, LOW, 250, 0);
    init(2, LOW, 500, 0);
    init(3, LOW, 1000, 0);

    while(1)
    {
        for (p_LED = LEDS; p_LED < &LEDS[N_LEDS]; p_LED++)
        {
            update(p_LED);
        }
    }
}
