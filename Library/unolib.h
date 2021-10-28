/* unolib: various commands to:
*	turn the built-in led on/off/tog
*	for ports B and D, set/clr/tog bit
*/

#ifndef UNOLIB_H
#define UNOLIB_H

#include <avr/io.h>
#include <util/delay.h>


enum {INPUT, OUTPUT, INPUT_PULLUP};
enum {LOW, HIGH, TOG};
enum {A0, A1, A2, A3, A4, A5};

void off_led () ;

void on_led () ;

void tog_led () ;

void set_bit (volatile uint8_t *port, uint8_t bit) ;

void clr_bit (volatile uint8_t *port, uint8_t bit) ;

void tog_bit (volatile uint8_t *port, uint8_t bit) ;

#endif