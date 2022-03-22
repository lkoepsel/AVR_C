#include "state2.h"

void state2() {
    digitalWrite(LED_bit0, LOW);
    digitalWrite(LED_bit1, HIGH);
    uint8_t unpressed = 1;

    while(unpressed) {
        // Up Button
        if (buttons[UP].pressed) {
            state = 3;
            unpressed = 0;
        }
        // Enter Button
        if (buttons[ENTER].pressed) {
            printf("State 2: Enter pressed, state = %d\n", state);

            blue_led(MEDIUM);
        }
    }
    blue_led_off();
    printf("Exiting State 2, state = %d\n", state);
    return;
}	
