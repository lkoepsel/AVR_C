#include "digitalRead.h"

uint8_t digitalRead(uint8_t apin) {
    // UNO PINS 0-7 PORT D        
    if (apin <= 7) {
        // Mask Port D input with pin then shift right to get the value in bit 0
        return((PIND & (1 << apin)) >> apin);
    }

    // UNO PINS 8-13 PORT B        
    else if (apin <= 13) {
        apin -= 8;
        return((PINB & (1 << apin)) >> apin);
    }
    return(255);
}  
