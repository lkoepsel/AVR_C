/*
* tenthTimer()
* Simple timer which toggles pin at 100Hz or 10ms timer.
* All at 50% duty cycle
* Example Settings:
* 25Hz: CS12 CS10 (clkIO/1024), OCR1A=156
* 100Hz: CS11 CS10 (clkIO/64), OCR1A=624
* 1kHz: CS11 only (clkIO/8), OCR1A=499 
* To calculate: 16x10^6 / scalar / OCR1A / 4
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "pinMode.h"
#include "digitalWrite.h"

ISR (TIMER1_OVF_vect)      
{
    digitalWrite(8, TOG);
}

void ioinit (void)          
{
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

    /* Set up pin for signal */
    pinMode(8, OUTPUT);

    /* Enable timer 1 overflow interrupt and enable interrupts. */
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
