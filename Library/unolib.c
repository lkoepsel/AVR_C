#include "unolib.h"

// https://www.nongnu.org/avr-libc/user-manual/FAQ.html#faq_softreset 
// Function Implementation
void wdt_init(void)
{
MCUSR = 0;
wdt_disable();
return;
}

uint16_t d_analogRead(uint8_t pin) 
{
   return (uint16_t) rand() % 1023; 
}

// use to ensure servo min/max are not exceeded, breaking the servo
uint8_t constrain8_t(uint8_t value, uint8_t min, uint8_t max) {
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }
    else
    {
        return value;
    }
}

// use to ensure servo min/max are not exceeded, breaking the servo
uint16_t constrain16_t(uint16_t value, uint16_t min, uint16_t max) {
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }
    else
    {
        return value;
    }
}

