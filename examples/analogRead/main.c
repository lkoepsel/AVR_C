#include <stdio.h>
#include "uart.h"
#include <avr/io.h>
#include "delay.h"
#include "unolib.h"
#include "pinMode.h"
#include "analogRead.h"

int main (void)
{
    init_serial;

    uint8_t analog_pin = A5;
    uint16_t max_value = 0;
    uint16_t min_value = 1023;
    uint16_t analog_value;

    puts("Testing analogRead");
    while(1) {
            analog_value = analogRead(analog_pin);
            if (analog_value > max_value) {
                max_value = analog_value;
            }
            else if (analog_value < min_value) {
                min_value = analog_value;
            }
            float voltage = 0.0048 * analog_value;
            printf("Pin: %d Value: %d Voltage: %6.2f Min: %d Max: %d\n",\
            analog_pin, analog_value, voltage, min_value, max_value);
            delay(2000);
    }
    return(0);
}
