#define delay 500
#include <avr/io.h>
#include <util/delay.h>

void blink (uint8_t times);

void clear_all_TC(void);

uint8_t analogWrite(uint8_t apin, uint8_t cycle) ;
