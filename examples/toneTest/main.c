/*
* toneTest()
* Determine if using Two timers, one can generate all the tones 
* from B0/31 Hz to D8/4978, all at 50% duty cycle
* When setting frequency, output will be divided by 4
*   Phase Correct timer divides by 2 => 62Hz 
*   Interrupt driven pin toggle divides by 2 as well => 31Hz at Pin 
* Example Settings:
* T0: 4978 Pin 7: COM0A1 WGM01 WGM00 CS01 CS00
* T1: 31Hz: Pin 8: COM1A1 WGM13 WGM11 WGM10 CS12 CS10 OCR1A=126
* https://github.com/bhagman/Tone
* https://itp.nyu.edu/physcomp/labs/labs-arduino-digital-and-analog/tone-output-using-an-arduino/
* Uses notes.h a file containing one set of definitions and two single dimension arrays:
*   definitions: notes as offsets into the arrays
*   notes_TCCR1B: scalar settings for a specific note, 
*   notes_OCR1A:  timer counter value req'd for a specific note
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "pinMode.h"
#include "digitalWrite.h"
#include "notes.h"


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

    int note7 = 55;
    int note8 = 23;
    /* Timer 0 is 8-bit PWM, PIN 7
    * COM0A1:0 =10 => Clear OC0A on Compare Match, set OC0A at BOTTOM
    * WGM02:0 = 101 => Phase Correct, TOP = OCRA
    * CS02:0 = 010 => clkI/O/8 (Prescaler)
    * Set OCR0A value to 126 => 16MHz / 1024 / 126 = 124Hz (divide by 4)
    * Limits for Timer 0:
    * 16MHz / 64 / 127 / 4 => 492Hz
    * 16MHz / 1024 / 126 /4 => 31Hz
    */ 
    TCCR0A |=  _BV(COM0A1) | _BV(WGM00);
    TCCR0B = pgm_read_byte(&(notes_TCCR0B[note7]));
    OCR0A = pgm_read_word(&(notes_OCR0A[note7]));

    /* Timer 1 is 10-bit PWM, PIN 8 
    * COM1A1:0 =10 => Clear OC1A/OC1B on Compare Match when up-counting
    * WGM13:0 = 1001 => PWM, Phase and Frequency Correct, TOP = OCR1A
    * CS12:0 = 011 => clkI/O/64 (From prescaler)
    * 
    */
    TCCR1A |=  _BV(COM1A1) | _BV(WGM10);
    TCCR1B = pgm_read_byte(&(notes_TCCR1B[note8]));
    OCR1A = pgm_read_word(&(notes_OCR1A[note8]));

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
