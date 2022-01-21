/*
* sysclock - use millis() which returns a long int of current tick counter
* Sets up a system tick of 1 millisec (1kHz)
* To test, uses the system delay (blocking, doesn't use clock)
* to determine delta between a delay
* tick Settings:
* To calculate: 16x10^6 / scalar / OCR1A / 2
* 1kHz: 16x10^6 / 8 / 1000 / 2 =>  1000  

*/
#ifndef sysclock_h
#define sysclock_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

uint16_t millis();
uint16_t micros();

/* Timer/Clock Scalar definitions
*	format SCALARn_s where:
*		n = 01 for T/C0 and T/C1, 2 for T/C2
*		s = scalar value as in 1, 8, 64, 128 etc
*	SCALARm is the default scalar for T/C m(m=0-2)
*	change the value for SCALARm to change the specific clock scalar
*/	
#ifndef SCALAR0
#define SCALAR0 SCALAR01_8
#endif
#ifndef SCALAR1
#define SCALAR1 SCALAR01_64
#endif
#ifndef SCALAR2
#define SCALAR2 SCALAR02_8
#endif
#ifndef SET_OCR1A
#define SET_OCR1A 128
#endif

#define RESET_MASK  0b11000111

void init_sysclock_0 (void);
void init_sysclock_1 (void);
void init_sysclock_2 (void);

uint8_t is_RESET_pressed();
uint8_t read_RESET();

#endif