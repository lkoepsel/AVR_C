// Pulse servo code

#include "delay.h"
#include "servo.h"

int main (void)
{
  // Set up a system tick of 1 millisec (1kHz)
  init_servos ();

  // index, bit, port, state, high_width)
  init_servo(0,4, &PORTD, LOW, 40);
  init_servo(1,1, &PORTB, LOW, 500);

    while(1)
    {
        delay(10);
    }
}
