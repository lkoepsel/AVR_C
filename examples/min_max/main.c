/* min_max - Demonstrates how to implement both min and max functions:
*   min(value, min) - Calculates the minimum of two numbers
*   max(value, max) - Calculates the maximum of two numbers
*/
#include <stdio.h>
#include "uart.h"
#include "delay.h"
#include "pinMode.h"
#include "analogRead.h"
#include "sysclock.h"

int main (void)
{
    init_serial();
    init_sysclock_2();

    const uint8_t analog_pin = A0;
    uint16_t max_value = 0;
    uint16_t min_value = 1023;

    puts("Testing analogRead with min()/max()");
    while(1) 
    {
        uint16_t analog_value = analogRead(analog_pin);

        min_value = min(analog_value, min_value);
        max_value = max(analog_value, max_value);
        printf("Pin: %u Value: %u Min: %u Max: %u\n",\
        analog_pin, analog_value, min_value, max_value);
        delay(2000);
    }
    return 0;
}
