#include "digitalWrite.h"

uint8_t digitalWrite(uint8_t apin, uint8_t level) {
    uint8_t bit, errno = 0;
    if ((apin >= 0) || (apin <= 7)) {
        bit = apin;
        // UNO PINS 0-7 PORT D        
        if (level == LOW) {
            PORTD &= ~_BV(bit);
        }
        else if (level == HIGH) {
            PORTD |= _BV(bit);        
        }
        else {
            errno = 1;
        }
        return(errno);
    }

    if ((apin >= 8) || (apin <= 13)) {
        bit = apin - 8;
        // UNO PINS 8-13 PORT B        
        if (level == LOW) {
            PORTB &= ~_BV(bit);
        }
        else if (level == HIGH) {
            PORTB |= _BV(bit);        
        }
        else {
            errno = 1;
        }
    }

    return(errno);
}  
