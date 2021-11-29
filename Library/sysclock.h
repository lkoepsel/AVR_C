/*
* sysclock - use millis() which returns a long int of current tick counter
* Sets up a system tick of 1 millisec (1kHz)
* To test, uses the system delay (blocking, doesn't use clock)
* to determine delta between a delay
* tick Settings:
* To calculate: 16x10^6 / scalar / OCR1A / 2
* 1kHz: 16x10^6 / 8 / 1000 / 2 =>  1000  

* button - each button must attach to a pin
* Requires sysclock to have a SCALAR1 = SCALAR01_64, as this provides a 8 millis pulse
* buttons[i].uno are the Uno pins attached to buttons, 
* like digitalRead, function will translate Uno pin to port/pin
* buttons[i].pressed indicates if the button has been pressed (true or non-zero)
*/
#ifndef sysclock_h
#define sysclock_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define max_buttons 2
#define BOUNCE_MASK 0b11000111

typedef struct button {
   uint8_t uno;                 // Uno pin numbers for button
   uint8_t pressed;             // true if button has been pressed
} button;

button buttons[max_buttons];

uint16_t millis();

uint8_t read_button(uint8_t button);

uint8_t is_button_pressed(uint8_t button);

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

void init_sysclock (void);
#endif