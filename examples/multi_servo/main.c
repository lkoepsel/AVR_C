// Pulse servo code

#include <stdio.h>
#include "delay.h"
#include "map.h"
#include "servo.h"
#include "uart.h"

int main (void)
{

    // index, bit, port, state, high_width)
    set_servo(0,2, &PORTD, LOW, HIGH_COUNT_MIN);
    set_servo(1,3, &PORTD, LOW, HIGH_COUNT_MAX);
    set_servo(2,4, &PORTD, LOW, HIGH_COUNT_MIN);
    set_servo(3,0, &PORTB, LOW, HIGH_COUNT_MAX);
    set_servo(4,1, &PORTB, LOW, HIGH_COUNT_MIN);
    set_servo(5,1, &PORTB, LOW, HIGH_COUNT_MAX);

    // Initialize servo clock to enable servos
    init_servos ();
    init_serial();

    while(1)
    {
        unsigned short servo;
        unsigned int angle;
        printf("Enter servo and servo angle separated by a blank: EX:2 120 ");
        scanf("%1hu %3u", &servo, &angle);
        printf("Moving servo %hu to angle %u \t", servo, angle);
        unsigned int servo_pulse = map(angle, 0, 180, HIGH_COUNT_MIN,\
            HIGH_COUNT_MAX);
        unsigned int safe_pulse = constrain16_t(servo_pulse,\
            HIGH_COUNT_MIN, HIGH_COUNT_MAX);

        printf("Pulse width will be: %u\n", safe_pulse);
        set_servo(servo,1, &PORTB, LOW, HIGH_COUNT_MAX);
    }
}
