#include "state0.h"

void state0() {
    digitalWrite(LED_bit0, LOW);
    digitalWrite(LED_bit1, LOW);
    uint8_t unpressed = 1;

    while(unpressed) {
        // Up Button
        if (buttons[UP].pressed) {
            state = 1;
            unpressed = 0;
        }
        // Enter Button
        if (buttons[ENTER].pressed) {
            state = 0;
            unpressed = 0;
        }
    }
    printf("Exiting State 0, state = %d\n", state);
    return;
}	
