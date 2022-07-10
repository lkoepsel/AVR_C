/* delay(uint16_t ms)
*   gcc-based delay() for simplicity and is accurate, is a blocking delay
*   Uses built-in delay_ms for delay, allows for passing a variable as a delay period
*/

#ifndef DELAY_H
#define DELAY_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

void delay(uint16_t ticks) ;
#endif