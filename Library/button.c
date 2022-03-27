#include "button.h"
#include "unolib.h"

button buttons[MAX_BUTTONS];


uint8_t read_button(uint8_t uno) {

    // UNO PINS 0-7 PORT D        
    if (uno <= 7) {
        // Mask Port D input with pin then shift right to get the value in bit 0
        return((PIND & (1 << uno)) == 0);
    }

    // UNO PINS 8-13 PORT B        
    else if (uno <= 13) {
        uno -= 8;
        return((PINB & (1 << uno)) == 0);
    }

    return(0);
}

uint8_t is_button_pressed(uint8_t instance){

    static uint8_t button_history[MAX_BUTTONS];
    uint8_t pressed = 0;    
 
    button_history[instance] = button_history[instance] << 1;
    button_history[instance] |= read_button(buttons[instance].uno);

    if ((button_history[instance] & BOUNCE_MASK) == 0b00000111){ 
        pressed = 1;
        button_history[instance] = 0b11111111;
    }
    return pressed;
}
