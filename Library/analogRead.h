/* analogRead(pin): read the value on pins A0-A5
*	Returns a value from 0-1023, based on value on AREF pin - 1
*/

#ifndef ANALOGREAD_H
#define ANALOGREAD_H

#include <avr/io.h>

uint16_t analogRead(uint8_t apin) ;
#endif