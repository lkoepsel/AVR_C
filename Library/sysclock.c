#include "sysclock.h"
#include "unolib.h"
volatile uint16_t sys_ctr = 0;

ISR (TIMER1_COMPA_vect)      
{
    sys_ctr--;
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
