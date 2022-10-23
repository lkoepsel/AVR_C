// servo code

#include "servo.h"

const uint16_t servo_pulse_width = 1000;
servo servos[MAX_SERVOS];

void init_servos (void)
{
  init_pulse_0 ();
  return;
}

void init_servo(uint8_t index, uint8_t bit, volatile uint8_t *port, uint8_t state,\
    uint16_t high_width)
{
    servos[index].bit = bit;
    servos[index].port = port;
    servos[index].state = state;
    servos[index].high_width = high_width;
    servos[index].low_width = servo_pulse_width - high_width;
    servos[index].high_count = high_width;
    servos[index].low_count = servos[index].low_width;

    // DDRn is 1 addr below PORTn, decrement and make a pointer to ref DDRn
    set_bit(*--servos[index].port, servos[index].bit);
    return ;
}

