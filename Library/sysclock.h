/*
* sysclock - use millis() which returns a long int of current tick counter
* Sets up a system tick of 1 millisec (1kHz)
* To test, uses the system delay (blocking, doesn't use clock)
* to determine delta between a delay
* There appears to be a lag of 8-9 millis as the delta is 1008
* tick Settings:
* 1kHz: CS11 only (clkIO/8), OCR1A=1008  
* To calculate: 16x10^6 / scalar / OCR1A / 4
*/
#ifndef sysclock_h
#define sysclock_h


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/atomic.h>
#include <stdio.h>

uint16_t millis() ;

void init_sysclock (void);
#endif