/* delay(uint16_t ms)
*   gcc-based delay() for simplicity and is accurate, blocking to meet needs
*   Uses built-in delay_ms for delay, allows for passing a variable.
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void delay(uint16_t ticks) ;
