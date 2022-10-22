// servo code

#include "servo.h"
#include "pinMode.h"

const uint16_t servo_pulse_width = 1000; 

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

    // TODO: replace DDRD with DDRn and use either port B or port D
    // use native command to set pin to output
    // DDRn is 1 address below PORTn
    // uint8_t DDRn = --*servos[index].port;
    // set_bit(DDRn, servos[index].bit);
    // set_bit(DDRD, servos[index].bit);
    
    return ;
}

