#include "sysclock.h"
#include "unolib.h"
volatile uint16_t sys_ctr = 0;

// extern button buttons[max_buttons];

/* ISR for system counter and button presses 
* 15ms of the delay is due to the button press checking in the ISR
* if button presses aren't required, comment out the code
*/
ISR (TIMER1_COMPA_vect)      
{
    /* button press check: make SCALAR1 SCALAR01_64 in sysclock.h   */
    /* and uncomment code below                                     */
    // for (int i = 0; i < max_buttons; i++) {
    //     buttons[i].pressed = is_button_pressed(i);
    // }

    PINB |= _BV(PB0);
    sys_ctr++;
}

uint16_t millis() {

      return(sys_ctr);
}

void init_sysclock (void)          
{
    /* * Initialize timer 1
    * CS12:0 = 010 => clkI/O/8 (From prescaler)
    * WGM13:0 = 1001 => PWM, Phase and Frequency Correct, TOP = OCR1A */
    TCCR1A |= _BV(WGM10) | _BV(COM1A0);
    // TCCR1B |= _BV(WGM13) | _BV(CS11);
    TCCR1B = SCALAR1;
    TCCR1B |= _BV(WGM13);

    /* Set OCR1A (TOP) value to 1000 => 16MHz / 8 / 1000 = 2000
    *  Phase Correct timer divides by 2 => 1000 Hz 
    */
    OCR1A = 40;
    DDRB |= _BV(PB1);

    /* Enable timer 1 A and B interrupts */
    TIMSK1 |= _BV(OCIE1A);
    sei ();
}
