// Pulse servo code

#include "delay.h"
#include "servo.h"

int main (void)
{

    // index, bit, port, state, high_width)
    init_servo(0,2, &PORTD, LOW, 40);
    init_servo(1,3, &PORTD, LOW, 60);
    init_servo(2,4, &PORTD, LOW, 100);

    // Initialize servo clock to enable servos
    init_servos ();

    while(1)
    {
        delay(10);
    }
}
