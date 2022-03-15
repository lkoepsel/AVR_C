#include "state3.h"

void state3() {
    digitalWrite(LED_bit0, HIGH);
    digitalWrite(LED_bit1, HIGH);
    uint8_t unpressed = 1;

    while(unpressed) {
        // Up Button
        if (buttons[UP].pressed) {
            state = 0;
            unpressed = 0;
        }
        // Enter Button
        if (buttons[ENTER].pressed) {
            printf("In Enter State 3, state = %d\n", state);

            blue_led(BRIGHT);

        }
    }
    blue_led_off();
    printf("Exiting State 3, state = %d\n", state);
    return;
}	
