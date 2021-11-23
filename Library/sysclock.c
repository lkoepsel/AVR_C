#include "sysclock.h"
volatile uint16_t sys_ctr = 0;


ISR (TIMER1_OVF_vect)      
{
    sys_ctr--;
}

uint16_t millis() {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
      return(sys_ctr);
    }
    /* dummy return to resolve compiler warning */
    return 0;
}

void init_sysclock (void)          
{
    /* Timer 1 is 10-bit PWM 
    * TCCR1A = TIMER1_PWM_INIT;
    * COM1A1:0 =10 => Clear OC1A/OC1B on Compare Match when up-counting */
    TCCR1A |=  _BV(COM1A1) | _BV(WGM10);

    /* * Start timer 1.
    * CS12:0 = 011 => clkI/O/8 (From prescaler)
    * WGM13:0 = 1001 => PWM, Phase and Frequency Correct, TOP = OCR1A */
    TCCR1B |= _BV(WGM13) | _BV(CS11);

    /* Set PWM value to 499 => 16MHz / 8 / 1000 = 2000
    *  Phase Correct timer divides by 2 => 1000 Hz 
    *  Pin toggle divides by 2 as well => 500 Hz at Pin 8 */
    OCR1A = 1001;

    /* Set up pin for signal */
    /* Enable timer 1 overflow interrupt and enable interrupts. */
    TIMSK1 = _BV (TOIE1);
    sei ();
}

