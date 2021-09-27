/*
* tenthTimer()
* Simple timer which toggles pin at 100Hz or 10ms timer.
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "pinMode.h"
#include "digitalWrite.h"

ISR (TIMER1_OVF_vect)       /* Note [2] */
{
    digitalWrite(8, TOG);
}

void ioinit (void)           /* Note [6] */
{
    /* Timer 1 is 10-bit PWM 
    * TCCR1A = TIMER1_PWM_INIT;
    * COM1A1:0 =10 => Clear OC1A/OC1B on Compare Match when up-counting
    * WGM2:0 =011 => PWM, Phase Correct, 10-bit
    */
    TCCR1A |=  _BV(COM1A1) | _BV(WGM11) | _BV(WGM10);
    /*
    * Start timer 1.
    * CS12:0 = 011 => clkI/O/64 (From prescaler)
    * WGM13 = 1 => PWM, Phase Correct, TOP = OCR1A 
    */
    TCCR1B |= _BV(WGM13) | _BV(CS11) | _BV(CS10);
    /* Set PWM value to 624 => 16MHz / 64 / 624 = 400
    *  Phase Correct timer provides 200Hz clock
    *  Pin toggle divides by 2 as well => 100Hz at Pin
    */
    OCR1A = 624;

    /* Enable timer 1 overflow interrupt. */
    TIMSK1 = _BV (TOIE1);
    sei ();
}

int main (void)
{
    ioinit ();

    /* loop forever, the interrupts are doing the rest */
    for (;;)  {          /* Note [7] */
        // sleep_mode();
        sleep_mode();
    }
    return (0);
}
