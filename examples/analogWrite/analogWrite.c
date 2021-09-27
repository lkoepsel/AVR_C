/* test analogWrite(pin, n): setup the Timer/Counters to provide a PWM signal */
#include "analogWrite.h"

int main (void)
{   
    clear_all_TC();
    off_led();

    uint8_t ard, duty_cycle;

    ard = 3;
    duty_cycle = 127; // 127 = 50%
    analogWrite(ard, duty_cycle);

    ard = 5;
    duty_cycle = 63; // 63 = 25%
    analogWrite(ard, duty_cycle);

    return(0);
}
