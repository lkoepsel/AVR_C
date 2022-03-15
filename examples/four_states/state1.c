#include "state1.h"

void state1() {
    digitalWrite(LED_bit0, HIGH);
    digitalWrite(LED_bit1, LOW);
    uint8_t unpressed = 1;

    while(unpressed) {
        // Up Button
        if (buttons[UP].pressed) {
            state = 2;
            unpressed = 0;
        }
        // Enter Button
        if (buttons[ENTER].pressed) {
            printf("In Enter State 1, state = %d\n", state);

            blue_led(DIM);
        }
    }

    blue_led_off();
    printf("Exiting State 1, state = %d\n", state);
    return;
}	
