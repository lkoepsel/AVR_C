#include "state2.h"

void state2() {
    digitalWrite(BIT_0, LOW);
    digitalWrite(BIT_1, HIGH);
    uint8_t unpressed = 1;

    while(unpressed) {
        // Up Button
        if (buttons[UP].pressed) {
            state = 3;
            unpressed = 0;
            printf("State2: Up pressed, state = %d\n", state);
        }
        // Enter Button
        if (buttons[ENTER].pressed) {
            state = 2;
            unpressed = 1;
            printf("State 2: Enter pressed, state = %d\n", state);
            blue_led(MEDIUM);
        }
    }
    blue_led_off();
    printf("Exiting State 2, state = %d\n", state);
    return;
}	
