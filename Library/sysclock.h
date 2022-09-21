/*
* sysclock - use ticks() which returns a long int of current tick counter
* Sets up a system tick of 62.5ns or 16MHz
* To test, uses the system delay (blocking, doesn't use clock)
* Measure pre-delay, measure post-delay, determine delta 
* between a delay then shift right by 4 to get microseconds
* 
* The three Timer/Counters are used in the following manner:
* T/C 0 - is used by tone to generate musical notes
* T/C 1 - is a free-running (CTC mode) 16 bit timer providing ticks()
* T/C 2 - is a 1 millisecond timer which also provides a 10ms debounce clock
*/
#ifndef sysclock_h
#define sysclock_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "tone.h"

uint16_t micros(void);
uint16_t millis(void);
uint16_t ticks(void);

void init_sysclock_0 (void);
void init_sysclock_1 (void);
void init_sysclock_2 (void);
void init_RESET(void);

uint8_t is_RESET_pressed(void);
uint8_t read_RESET(void);

#endif