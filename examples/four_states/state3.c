#include "state3.h"

void state3() {
    digitalWrite(BIT_0, HIGH);
    digitalWrite(BIT_1, HIGH);
    uint8_t unpressed = 1;

    while(unpressed) {
        // Up Button
        if (buttons[UP].pressed) {
            state = 0;
            unpressed = 0;
            printf("State3: Up pressed, state = %d\n", state);
        }
        // Enter Button
        if (buttons[ENTER].pressed) {
            state = 3;
            unpressed = 1;
            printf("State 3: Enter pressed, state = %d\n", state);
            blue_led(BRIGHT);

        }
    }
    blue_led_off();
    printf("Exiting State 3, state = %d\n", state);
    return;
}	
