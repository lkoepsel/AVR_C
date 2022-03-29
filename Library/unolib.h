/* unolib: various commands to:
*	turn the built-in led on/off/tog
*	for ports B and D, set/clr/tog bit
*/

#ifndef UNOLIB_H
#define UNOLIB_H

/* User Push Button on ATmega328PB XPLAINED Board is PB7
*  It is ACTIVE LOW
*  If using a different board or pin, adjust accordingly! 
*  See: https://hackaday.com/2015/12/10/embed-with-elliot-debounce-your-noisy-buttons-part-ii/#more-180185
*  for a explanation of the routine
*/

#if SOFT_RESET
#define RESET_BUTTON PB7
#define RESET_MASK  0b11000111
#endif

#define BOUNCE_DIVIDER 20 // divides millis by this number for checking reset button

/* Arduino Definitions handy for AVR_C      */
#define LED_BUILTIN 13

#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>


enum {INPUT, OUTPUT, INPUT_PULLUP};
enum {LOW, HIGH, TOG};
enum {A0, A1, A2, A3, A4, A5};

// https://www.nongnu.org/avr-libc/user-manual/FAQ.html#faq_softreset 
// Function Pototype
void wdt_init(void) __attribute__((naked)) __attribute__((section(".init3")));

#define soft_reset() \
do \
{ \
wdt_enable(WDTO_15MS); \
for(;;) \
{ \
} \
} while(0)

#define set_bit(port, bit) ((port) |= (1 << (bit)))
#define clr_bit(port, bit) ((port) &= ~(1 << (bit)))
#define tog_bit(port, bit) ((port) |= (1 << (bit)))

#endif