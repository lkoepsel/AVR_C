/*
* twoTimers()
* Two timers which toggles pins at 100Hz and 500Hz using timer 0 and timer 1.
* All at 50% duty cycle
* Example Settings:
* T0: 500Hz Pin 7: COM0A1 WGM01 WGM00 CS01 CS00
* T1: 100Hz: COM1A1 WGM13 WGM11 WGM10 CS11 CS10 OCR1A=624
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "pinMode.h"
#include "digitalWrite.h"

ISR (TIMER0_OVF_vect)      
{
    digitalWrite(7, TOG);
}

ISR (TIMER1_OVF_vect)      
{
    digitalWrite(8, TOG);
}

void ioinit (void)          
{
    /* Timer 0 is 8-bit PWM 
    * TCCR0A = TIMER1_PWM_INIT;
    * COM0A1:0 =10 => Clear OC0A on Compare Match, set OC0A at BOTTOM */
    TCCR0A |=  _BV(COM0A1) | _BV(WGM01) | _BV(WGM00);

    /* * Start timer 1.
    * CS02:0 = 011 => clkI/O/64 (From prescaler)
    * WGM02:0 = 011 => Fast PWM, Phase Correct, TOP = 0xFF */
    TCCR0B |=  _BV(CS01) | _BV(CS00);

    /* Set PWM value to 624 => 16MHz / 64 / 624 = 400
    *  Phase Correct timer divides by 2 => 200Hz 
    *  Pin toggle divides by 2 as well => 100Hz at Pin */
    // OCR1A = 624;

    /* Timer 1 is 10-bit PWM 
    * TCCR1A = TIMER1_PWM_INIT;
    * COM1A1:0 =10 => Clear OC1A/OC1B on Compare Match when up-counting */
    TCCR1A |=  _BV(COM1A1) | _BV(WGM11) | _BV(WGM10);

    /* * Start timer 1.
    * CS12:0 = 011 => clkI/O/64 (From prescaler)
    * WGM13:0 = 1011 => PWM, Phase Correct, TOP = OCR1A */
    TCCR1B |= _BV(WGM13) | _BV(CS11) | _BV(CS10);

    /* Set PWM value to 624 => 16MHz / 64 / 624 = 400
    *  Phase Correct timer divides by 2 => 200Hz 
    *  Pin toggle divides by 2 as well => 100Hz at Pin */
    OCR1A = 624;

    /* Set up pins for signal */
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);

    /* Enable timer 1 overflow interrupt and enable interrupts. */
    TIMSK0 = _BV (TOIE0);
    TIMSK1 = _BV (TOIE1);
    sei ();
}

int main (void)
{
    ioinit ();

    /* loop forever, the interrupts are doing the rest */
    for (;;)  {         
        // sleep_mode();
        sleep_mode();
    }
    return (0);
}
