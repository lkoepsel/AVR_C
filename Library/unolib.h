// unolib: various commands to:
//	turn the built-in led on/off/tog
//	for ports B and D, set/clr/tog bit
//  d_analogRead() - is a dummy analogRead which returns a rand 0-1023

#ifndef UNOLIB_H
#define UNOLIB_H

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>

// min/max functions as macros, taken from The C Language, K&R
#define min(a, b) ((a) < (b) ? (a) : (b)) 
#define max(a, b) ((a) > (b) ? (a) : (b))


// pin to Port functions, to make it easy to convert Uno pin to 328P port
#define pintoBit(a) ((a) < 8 ? (a) : (a - 8))
#define pintoPort(a) ((a) < 8 ? (&PORTD) : (&PORTB))

#define LED_BUILTIN 13

enum {INPUT, OUTPUT, INPUT_PULLUP};
enum {LOW, HIGH, TOG};
enum {A0, A1, A2, A3, A4, A5};
enum {FALSE, TRUE};

uint16_t d_analogRead(uint8_t pin) ;
uint8_t constrain8_t(uint8_t value, uint8_t min, uint8_t max);
uint16_t constrain16_t(uint16_t value, uint16_t min, uint16_t max);

/* User Push Button on ATmega328PB XPLAINED Board is PB7
*  It is ACTIVE LOW
*  If using a different board or pin, adjust accordingly! 
*  See: https://hackaday.com/2015/12/10/embed-with-elliot-debounce-your-noisy-buttons-part-ii/#more-180185
*  for a explanation of the routine
*/

#define RESET_BUTTON PB7
#define RESET_MASK  0b11000111

#define BOUNCE_DIVIDER 32 // divides millis by this number for checking reset button

// https://www.nongnu.org/avr-libc/user-manual/FAQ.html#faq_softreset 
// Function Prototype
void wdt_init(void) __attribute__((naked)) __attribute__((section(".init3")));

#define soft_reset() \
do \
{ \
wdt_enable(WDTO_15MS); \
for(;;) \
{ \
blink();\
} \
} while(0)

#endif

// inline blink, used to indicate a soft reset, blinks pin 13
#define blink() \
DDRB |= (_BV(PORTB5));\
PORTB |= (_BV(PORTB5));\
_delay_ms(100);\
PORTB &= ~(_BV(PORTB5));

// inline tog, used to test if ISR is firing, toggles pin 13
#define tog() \
DDRB |= (_BV(PORTB5));\
PINB |= (_BV(PORTB5));

#define set_bit(port, bit) ((port) |= (1 << (bit)))
#define clr_bit(port, bit) ((port) &= ~(1 << (bit)))
#define tog_bit(port, bit) ((port) |= (1 << (bit)))
