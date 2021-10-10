/*
* delay(uint16_t ms)
* Simple timer which toggles pin at 1000Hz or 1ms timer. All at 50% duty cycle.
* Use as a dynamic delay, will accept n milliseconds 
* and doesn't return until n ms has elasped.
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "pinMode.h"
#include "digitalWrite.h"

uint16_t volatile count1;

void initT1 (void) ;

uint8_t delay(uint16_t ms) ;
