/* test analogWrite(pin, n): setup two Timer/Counters to provide a PWM signal 
*   Provides a 50% duty cycle, 488Hz on ard_pin1 and 25%, 976Hz signal on ard_pin2
*/
#include "analogWrite.h"

int main (void)
{   
    // Use clear_all_TC to initialize all timer/counters to 0.
    // Not always needed, however helpful if you are getting unexpected results
    clear_all_TC();

    uint8_t duty_cycle;

    const uint8_t pin1 = 3;
    duty_cycle = 127; // 127/255 = 50%
    analogWrite(pin1, duty_cycle);

    const uint8_t pin2 = 2;
    duty_cycle = 63; // 63/255 = 25%
    analogWrite(pin2, duty_cycle);

    return 0;
}
