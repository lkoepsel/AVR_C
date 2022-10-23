// servo - each servo must attach to a pin

#ifndef SERVO_H
#define SERVO_H

#include "sysclock.h"
#include "delay.h"

#define MAX_SERVOS 6

typedef struct servo {
   uint8_t bit;               // ATmega328P pin bit
   volatile uint8_t *port;    // ATmega328P port for pin 
   uint8_t state;             // is pulse HIGH or LOW
   uint16_t high_width;       // pulse time on
   uint16_t low_width;        // pulse            // pulse time off
   uint16_t high_count;       // used by ISR to track n high counts
   uint16_t low_count;        // used by ISR to track n low counts
} servo;

extern servo servos[MAX_SERVOS];

void init_servos (void);
void init_servo(uint8_t index, uint8_t bit, volatile uint8_t *port, uint8_t state,\
    uint16_t high_width);

#endif
