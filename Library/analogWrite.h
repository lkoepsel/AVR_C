#define delay 500
#include <avr/io.h>
#include <util/delay.h>

void blink (short int times);

void clear_all_TC(void);

short int analogWrite(short int apin, short int cycle) ;
