/* digitalWrite(pin, level): set pin on Ports B and D to a level LOW/HIGH/TOG
*/

#ifndef DIGITALWRITE_H
#define DIGITALWRITE_H

#include <util/delay.h>
#include <avr/io.h>
#include "unolib.h"

// volatile uint8_t *pintoPort(uint8_t apin);
void digitalWrite(uint8_t apin, uint8_t level) ;

#endif