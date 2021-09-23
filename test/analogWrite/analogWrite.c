/* test analogWrite(pin, n): setup the Timer/Counters to provide a PWM signal */
#include "analogWrite.h"
#include "avr_uno.h"

int main (void)
{   
    clear_all_TC();

    short int ard, duty_cycle;

    ard = 10;
    duty_cycle = 127; // 127 = 50%
    if (analogWrite(ard, duty_cycle)) {
        blink(2);
    }

    ard = 11;
    duty_cycle = 63; // 63 = 25%
    if (analogWrite(ard, duty_cycle)) {
        blink(4);
    }
    off_led();
}
