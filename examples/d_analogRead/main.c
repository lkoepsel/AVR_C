// d_analogRead - Demonstrates a dummy version of analogRead using
// a random number generator rand(). Remaining logic, identical to analogRead example
// Cast is used on return to ensure the specific type, otherwise it would be an int
// Reference voltage is assumed to be 5V, each step 5V/1024 or .00488
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "delay.h"
#include "unolib.h"

uint16_t d_analogRead(uint8_t pin) 
{
   return (uint16_t) rand() % 1023; 
}

void d_pinMode() { }  // add pin and INPUT, when Library pinMode() is used

int main (void)
{
    init_serial();

    const uint8_t analog_pin = A0;
    d_pinMode(); // add pin and INPUT, when Library pinMode() is used

    puts("Testing dummy analogRead");
    while(1) {
            uint16_t analog_value = d_analogRead(analog_pin);
            float voltage = (analog_value * .00488);
            printf("Pin: %u Value: %u Voltage: %5.3f\n",\
            analog_pin, analog_value, voltage);
            delay(1000);
    }
    return 0;
}
