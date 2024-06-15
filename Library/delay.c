#include "delay.h"

void delay(uint16_t ms) 
{
    /* Simple loop which allows variables */
    for (uint16_t i = 1; i <= ms; i++)
    {
      _delay_ms(1);
    }
}

void delay_us(uint16_t us) {


    /* Simple loop which allows variables */
    for (uint16_t i = 1; i <= us; i++)
    {
      _delay_us(1);
    }
}