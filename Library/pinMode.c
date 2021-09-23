#include "pinMode.h"


uint8_t pinMode(uint8_t apin, uint8_t mode) {
    uint8_t bit, errno = 0;
    if ((apin >= 0) || (apin <= 7)) {
        bit = apin;
        // UNO PINS 0-7 PORT D        
        if (mode == INPUT) {
            DDRD &= ~_BV(bit);
        }
        else if (mode == OUTPUT) {
            DDRD |= _BV(bit);
        }
        else if (mode == INPUT_PULLUP) {
            DDRD &= ~_BV(bit);
            PORTD |= _BV(bit);
        }
        else {
            errno = 1;
        }
    }

    // UNO PINS 8-13 PORT B 0-5        
    if ((apin >= 8) || (apin <= 13)) {
        bit = apin;
        if (mode == INPUT) {
            DDRB &= ~_BV(bit);
        }
        else if (mode == OUTPUT) {
            DDRB |= _BV(bit);
        }
        else if (mode == INPUT_PULLUP) {
            DDRB &= ~_BV(bit);
            PORTB |= _BV(bit);
        }
        else {
            errno = 1;
        }
    }
    return(errno);
}  

