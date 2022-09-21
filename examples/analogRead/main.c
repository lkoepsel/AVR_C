// analogRead - Read an analog voltage on an analog pin (A0-A5)
// Reference voltage is assumed to be 5V, each step 5V/1024 or .00488
#include <stdio.h>
#include "uart.h"
#include "delay.h"
#include "pinMode.h"
#include "analogRead.h"

int main (void)
{
    init_serial();

    const uint8_t analog_pin = A0;
    pinMode(analog_pin, INPUT);

    puts("Testing analogRead");
    while(1) {
            uint16_t analog_value = analogRead(analog_pin);
            float voltage = (analog_value * .00488);
            printf("Pin: %u Value: %u Voltage: %5.3f %5.3e\n",\
            analog_pin, analog_value, voltage, voltage);
            delay(1000);
    }
    return 0;
}
