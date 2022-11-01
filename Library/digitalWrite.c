#include "digitalWrite.h"
 
void digitalWrite(uint8_t apin, uint8_t level) {
    volatile uint8_t *portn;
    uint8_t bit = pintoBit(apin);
    portn = pintoPort(apin);
    if (level == LOW) {
        clr_bit(*portn, bit);
    }
    else if (level == HIGH) {
        set_bit(*portn, bit);
    }
    else if (level == TOG) {
        // PINn is 2 addresses below PORTn, decrement twice then set to toggle
        portn--;
        portn--;
        set_bit(*portn, bit);
    }
    return;
}  
