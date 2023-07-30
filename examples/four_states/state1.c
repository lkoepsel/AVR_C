#include "state1.h"

void state1() {
    digitalWrite(BIT_0, HIGH);
    digitalWrite(BIT_1, LOW);
    uint8_t unpressed = 1;

    while(unpressed) {
        // Up Button
        if (buttons[UP].pressed) {
            state = 2;
            unpressed = 0;
            printf("State1: Up pressed, state = %d\n", state);
        }
        // Enter Button
        if (buttons[ENTER].pressed) {
            state = 1;
            unpressed = 1;
            blue_led(DIM);
            printf("State 1: Enter pressed, state = %d\n", state);
        }
    }

    blue_led_off();
    printf("Exiting State 1, state = %d\n", state);
    return;
}	
