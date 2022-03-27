#include "digitalWrite.h"

uint8_t digitalWrite(uint8_t apin, uint8_t level) {
    uint8_t bit, errno = 0;
    // UNO PINS 0-7 PORT D        
    if (apin <= 7) {
        bit = apin;
        if (level == LOW) {
            clr_bit(PORTD, bit);
        }
        else if (level == HIGH) {
            set_bit(PORTD, bit);
        }
        else if (level == TOG) {
            tog_bit(PIND, bit);
        }
        else {
            errno = -1;
        }
        return(errno);
    }

    // UNO PINS 8-13 PORT B        
    else if (apin <= 13) {
        bit = apin - 8;
        if (level == LOW) {
            clr_bit(PORTB, bit);
        }
        else if (level == HIGH) {
            set_bit(PORTB, bit);
        }
        else if (level == TOG) {
            tog_bit(PINB, bit);
        }
        else {
            errno = -1;
        }
    }
    else {
        return(errno);
    }
    return(errno);
}  
