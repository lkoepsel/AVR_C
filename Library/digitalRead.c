#include "digitalRead.h"

uint8_t digitalRead(uint8_t apin) {
    // UNO PINS 0-7 PORT D        
    if ((apin >= 0) && (apin <= 7)) {
        return(PIND & (1 << apin)) ;
    }

    // UNO PINS 8-13 PORT B        
    else if ((apin >= 8) && (apin <= 13)) {
        apin -= 8;
        return(PINB & (1 << apin));
    }
    return(255);
}  
