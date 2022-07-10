/* analogRead - This version of analogRead uses a 4.096V voltage shunt (a precise
*  voltage reference) to provide AREF voltage. This approach provides a more 
*  precise measurement than using VCC, the supply voltage. The conversion
*. is more simple using this approach as to convert a analog reading of 10bits 
*. (0-1023) to a reading from (0-4096), one simply shifts left 2 positions (x4)
*. then the reading will be in volts * 100. 
*  For example: 2.5V => 250 or 1.31V = 131
*/
#include <stdio.h>
#include <avr/io.h>
#include "uart.h"
#include "delay.h"
#include "unolib.h"
#include "pinMode.h"
#include "analogRead.h"
#include "sysclock.h"

int main (void)
{
    init_serial();
    init_sysclock_2();
//    init_RESET();

    const uint8_t analog_pin = A0;
    uint16_t max_value = 0;
    uint16_t min_value = 1023;

    puts("Testing analogRead");
    while(1) {
            uint16_t analog_value = analogRead(analog_pin);
            if (analog_value > max_value) 
            {
                max_value = analog_value;
            }
            else if (analog_value < min_value) 
            {
                min_value = analog_value;
            }
            uint16_t voltage = (analog_value << 2);
            printf("Pin: %u Value: %u Voltage: %u Min: %u Max: %u\n",\
            analog_pin, analog_value, voltage, min_value, max_value);
            delay(2000);
    }
    return(0);
}
