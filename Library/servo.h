// servo - servo is based on pulsing one servo per interrupt
// the timing of the pulses need two aspects, ~50Hz frequency
// width ranging from .5ms to 2.3ms
// To do this well, there are three parameters which need to be adjusted
// Use the block of defines below to specify the correct parameters
// You will need to confirm your pulse width values for your specific servo
// The values above provide approx .5ms to 2.3ms positive pulse widths at ~50Hz
// N servos less than 2, use servo_0 example which uses TC PWM directly
// N servos greater than 4 is not recommended
// Note that SERVO must be defined in env.make and an CPP flag as -DSERVO=$(SERVO)

#ifndef SERVO_H
#define SERVO_H

#include "sysclock.h"
#include "delay.h"

// Uncomment block of defines based on number of servos
// Parameters create a 52.1Hz frequency with pulse range .5ms to 2.3ms

// Using 2 servos
#define MAX_SERVOS 2
#define SERVO_PULSE_WIDTH 600
#define HIGH_COUNT_MAX 72
#define HIGH_COUNT_MIN 15

// Using 3 servos
// #define MAX_SERVOS 3
// #define SERVO_PULSE_WIDTH 400
// #define HIGH_COUNT_MAX 50
// #define HIGH_COUNT_MIN 12

// Using 4 servos
// #define MAX_SERVOS 4
// #define SERVO_PULSE_WIDTH 300
// #define HIGH_COUNT_MAX 36
// #define HIGH_COUNT_MIN 8

// Using 5 servos
// #define MAX_SERVOS 5
// #define SERVO_PULSE_WIDTH 240
// #define HIGH_COUNT_MAX 29
// #define HIGH_COUNT_MIN 6

// Using 6 servos
// #define MAX_SERVOS 6
// #define SERVO_PULSE_WIDTH 200
// #define HIGH_COUNT_MAX 24
// #define HIGH_COUNT_MIN 5

typedef struct servo {
   uint8_t bit;               // ATmega328P pin bit
   volatile uint8_t *port;    // ATmega328P port for pin 
   uint8_t state;             // is pulse HIGH or LOW
   uint16_t high_width;       // pulse time on
   uint16_t low_width;        // pulse            // pulse time off
   uint16_t high_count;       // used by interrupt to track n high counts
   uint16_t low_count;        // used by interrupt to track n low counts
} servo;

extern servo servos[MAX_SERVOS];

void init_servos (void);
void set_servo(uint8_t index, uint8_t bit, volatile uint8_t *port, uint8_t state,\
    uint16_t high_width);
void move_servo(uint8_t index, uint16_t high_width);

#endif
