// serialRead - Can replace analogRead() by getting the 10bit integer data
// from the serial port.
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "delay.h"
#include "unolib.h"
#include "serialRead.h"

int main (void)
{
    init_serial();

    const uint8_t analog_pin = A0;
    // d_pinMode(); // add pin and INPUT, when Library pinMode() is used

    puts("Testing serialRead, exits on non-numeric input");
    while(1) 
    {
        uint16_t analog_value;
        analog_value = serialRead();
        float voltage = (analog_value * .00488);
        printf("Pin: %u Value: %u Voltage: %5.3f\n",\
        analog_pin, analog_value, voltage);
        delay(1000);
    }
}
