#include "pinMode.h"

uint8_t pinMode(uint8_t apin, uint8_t mode) {
    uint8_t bit, errno = 0;
    if (apin <= 7) {
        bit = apin;
        // UNO PINS 0-7 PORT D        
        if (mode == INPUT) {
            clr_bit(DDRD, bit);
        }
        else if (mode == OUTPUT) {
            set_bit(DDRD, bit);
        }
        else if (mode == INPUT_PULLUP) {
            clr_bit(DDRD, bit);
            set_bit(PORTD, bit);
        }
        else {
            errno = 1;
        }
    }

    // UNO PINS 8-13 PORT B 0-5        
    else if (apin <= 13) {
        bit = apin - 8;
        if (mode == INPUT) {
            clr_bit(DDRB, bit);
        }
        else if (mode == OUTPUT) {
            set_bit(DDRB, bit);
        }
        else if (mode == INPUT_PULLUP) {
            clr_bit(DDRB, bit);
            set_bit(PORTB, bit);
        }
        else {
            errno = 1;
        }
    }
    else {
        return(errno);
    }
    return(errno);
}  
