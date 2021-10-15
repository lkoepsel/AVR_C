#include "delay.h"

void delay(uint16_t ticks) {

  uint16_t i;

    /* Simple loop which allows variables */
    for (i = 1; i <= ticks; i++){
      _delay_ms(1);
    }
}