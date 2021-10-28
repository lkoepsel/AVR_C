/* pinMode(pin, mode): set a pin on ports B and D to INPUT/OUTPUT/INPUT_PULLUP
*/

#ifndef PINMODE_H
#define PINMODE_H

#include <avr/io.h>
#include "unolib.h"

uint8_t pinMode(uint8_t apin, uint8_t mode) ;

#endif