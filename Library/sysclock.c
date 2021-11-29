#include "sysclock.h"
#include "unolib.h"
volatile uint16_t sys_ctr = 0;
volatile uint8_t buttons[max_buttons];
volatile uint8_t pins[max_buttons];

ISR (TIMER1_COMPA_vect)      
{
    sys_ctr--;
    for (int i = 0; i < max_buttons; i++) {
        buttons[i] = is_button_pressed(i);
    }
}

uint16_t millis() {

      return(sys_ctr);
}

void init_sysclock (void)          
{
    /* * Initialize timer 1
    * CS12:0 = 010 => clkI/O/8 (From prescaler)
    * WGM13:0 = 1001 => PWM, Phase and Frequency Correct, TOP = OCR1A */
    TCCR1A |= _BV(WGM10);
    // TCCR1B |= _BV(WGM13) | _BV(CS11);
    TCCR1B = SCALAR1;
    TCCR1B |= _BV(WGM13);

    /* Set OCR1A (TOP) value to 1000 => 16MHz / 8 / 1000 = 2000
    *  Phase Correct timer divides by 2 => 1000 Hz 
    */
    OCR1A = 1000;

    /* Enable timer 1 A and B interrupts */
    TIMSK1 |= _BV(OCIE1A);
    sei ();
}

uint8_t read_button(uint8_t bpin) {

    // UNO PINS 0-7 PORT D        
    if ((bpin >= 0) && (bpin <= 7)) {
        // Mask Port D input with pin then shift right to get the value in bit 0
        return((PIND & (1 << bpin)) >> bpin);
    }

    // UNO PINS 8-13 PORT B        
    else if ((bpin >= 8) && (bpin <= 13)) {
        bpin -= 8;
        return((PINB & (1 << bpin)) >> bpin);
    }

    return(0);
}


uint8_t is_button_pressed(uint8_t instance){

    static uint8_t button_history[max_buttons] = {0};
    uint8_t pressed = 0;    
 
    button_history[instance] = button_history[instance] << 1;

    button_history[instance] |= read_button(pins[instance]);

    if ((button_history[instance] & BOUNCE_MASK) == 0b00000111){ 
        pressed = 1;
        button_history[instance] = 0b11111111;
    }
    return pressed;
}