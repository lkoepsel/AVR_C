/* unolib: various commands to:
*	turn the built-in led on/off/tog
*	for ports B and D, set/clr/tog bit
*/

#ifndef UNOLIB_H
#define UNOLIB_H

/* User Push Button on ATmega328PB XPLAINED Board is PB7
*  It is ACTIVE LOW
*  If using a different board or pin, adjust accordingly! 
*/
#define RESET_BUTTON PB3

/* Arduino Definitions handy for AVR_C      */
#define LED_BUILTIN 13


#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>


enum {INPUT, OUTPUT, INPUT_PULLUP};
enum {LOW, HIGH, TOG};
enum {A0, A1, A2, A3, A4, A5};
enum {NO_CLOCK01, SCALAR01_1, SCALAR01_8, SCALAR01_64, SCALAR01_256, SCALAR01_1024};
enum {NO_CLOCK2, SCALAR2_1, SCALAR2_8, SCALAR2_32, SCALAR2_64, SCALAR2_128, SCALAR2_256, SCALAR2_1024};

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

void LED_off () ;

void LED_on () ;

void LED_tog () ;

#define set_bit(port, bit) ((port) |= (1 << (bit)))
#define clr_bit(port, bit) ((port) &= ~(1 << (bit)))
#define tog_bit(port, bit) ((port) |= (1 << (bit)))

#endif