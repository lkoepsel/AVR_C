/* constrain - Demonstrates how to implement constrain function
*   constrain(value, min, max) - constrains a value to be within two numbers
*/
#include <stdio.h>
#include <avr/io.h>
#include "uart.h"
#include "delay.h"
#include "unolib.h"
#include "pinMode.h"
#include "analogRead.h"
#include "sysclock.h"

uint16_t constrain(uint16_t value, uint16_t min, uint16_t max) {
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

int main (void)
{
    init_serial();
    init_sysclock_2();
//    init_RESET();

    const uint8_t analog_pin = A0;
    uint16_t top = 512;
    uint16_t bottom = 50;

    puts("Testing analogRead with min()/max()");
    while(1) 
    {
        uint16_t analog_value = analogRead(analog_pin);
        uint16_t value = constrain(analog_value, bottom, top);
        printf("Pin: %u Read Value: %u Value: %u \n",\
        analog_pin, analog_value, value);
        delay(2000);

    }
    return 0;
}
