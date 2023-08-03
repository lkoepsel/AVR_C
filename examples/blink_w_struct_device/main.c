// blink without delay using a struct array then add an init function
// the init function will simplify adding additional devices (LEDs, tones etc)
// uses a function pointer array to enable multiple devices
// currently uses only LEDs, however, tones could be added
#include "pinMode.h"
#include "digitalWrite.h"
#include "sysclock.h"

#define N_LEDS 3
#define N_DEVICES 3

struct blinker
{
  uint8_t Uno_pin;           // the number of the LED pin
  uint8_t state;            // the state (HIGH/LOW) the LED pin
  uint32_t interval;        // interval at which to blink (milliseconds)
  uint32_t previousMillis;  // will store last time LED was updated
} ;
struct blinker LEDS[N_LEDS];

struct device
{
  void (*device_func)(uint8_t i);   // function to control device
  uint8_t index;                    // index of specific device
} ;
struct device DEVICES[N_DEVICES];

void init(uint8_t index, void *device, uint8_t Uno_pin, uint8_t state, uint32_t interval,\
    uint32_t previousMillis)
{
    DEVICES[index].device_func = device;
    LEDS[index].Uno_pin = Uno_pin;
    LEDS[index].state = state;
    LEDS[index].interval = interval;
    LEDS[index].previousMillis = 0;

    pinMode(LEDS[index].Uno_pin, OUTPUT);
    return ;
}  

void LED(uint8_t i)
{
   uint32_t currentMillis = millis();
   if(currentMillis - LEDS[i].previousMillis > LEDS[i].interval)
   {
       LEDS[i].previousMillis = currentMillis;
       LEDS[i].state = !LEDS[i].state;
       digitalWrite(LEDS[i].Uno_pin, LEDS[i].state);
   }
}

int main (void)
{
    init_sysclock_2 ();

    // Parameters: index, LED, pin, state, interval, previous
    // Parameters: index, function, pin, state, interval, previous
    init(0, LED, 4, LOW, 250, 0);
    init(1, LED, 5, LOW, 500, 0);
    init(2, LED, 6, LOW, 1000, 0);

    while(1)
    {
        for (uint8_t device = 0; device < N_DEVICES; device++)
        {
            (*DEVICES[device].device_func)(device);
        }
    }
}
