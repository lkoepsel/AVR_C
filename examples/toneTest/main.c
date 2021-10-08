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

#include <stdio.h>
#include "uart.h"

volatile uint16_t count0;
volatile uint16_t count1;
volatile uint8_t pin0 = 7;
volatile uint8_t pin1 = 8;

ISR (TIMER0_OVF_vect)      
{

    if (count0 != 0) {
        count0--;
        digitalWrite(pin0, TOG);
    }
    digitalWrite(pin0, LOW);
}

ISR (TIMER1_OVF_vect)      
{

    if (count1 != 0) {
        count1--;
        digitalWrite(pin1, TOG);
    }
    digitalWrite(pin1, LOW);
}

void ioinit (void)          
{

    int note0 = 55;
    int note1 = 55;
    int duration0 = 8;
    int duration1 = 2;

    /* Timer 0 is 8-bit PWM, PIN 7
    * COM0A1:0 =10 => Clear OC0A on Compare Match, set OC0A at BOTTOM
    * WGM02:0 = 101 => Phase Correct, TOP = OCRA
    * CS02:0 = clkI/O/value (Prescaler) found in notes.h
    * Set OCR0A value via notes.h
    */ 
    TCCR0A |=  _BV(COM0A1) | _BV(WGM00);
    TCCR0B = pgm_read_byte(&(notes_TCCR0B[note0]));
    OCR0A = pgm_read_word(&(notes_OCR0A[note0]));

    /* Timer 1 is 10-bit PWM, PIN 8 
    * COM1A1:0 =10 => Clear OC1A/OC1B on Compare Match when up-counting
    * WGM13:0 = 1001 => PWM, Phase and Frequency Correct, TOP = OCR1A
    * CS12:0 = clkI/O/value (Prescaler) found in notes.h
    * Set OCR1A value via notes.h
    */
    TCCR1A |=  _BV(COM1A1) | _BV(WGM10);
    TCCR1B = pgm_read_byte(&(notes_TCCR1B[note1]));
    OCR1A = pgm_read_word(&(notes_OCR1A[note1]));

    /* Set up pins for signal */
    pinMode(pin0, OUTPUT);
    pinMode(pin1, OUTPUT);

    /* Use duration to determine count for interrupt 
    *  duration is a power of 2, so shift to divide by 2
    *  # of toggles is twice the freq, so count = duration/2
    */
    count0 = pgm_read_word(&(notes_freq[note0]));
    for (int i=(duration0 >> 1);i!=0;(i >>= 1)) {
        count0 >>= 1;
        printf("i= %d count0=%d\n", i, count0);
    }

    /* Use duration to determine count for interrupt */
    count1 = pgm_read_word(&(notes_freq[note1]));
    for (int i=(duration1 >>= 1);i!=0;i >>= 1) {
        count1 >>= 1;
        printf("i= %d count1=%d\n", i, count1);
    }
    printf("count0= %d\n", count0);
    printf("count1= %d\n", count1);

    /* Enable timer 1 overflow interrupt and enable interrupts. */
    TIMSK0 = _BV (TOIE0);
    TIMSK1 = _BV (TOIE1);
    sei ();
}

int main (void)
{
    uart_init();
    stdout = &uart_output;
    stdin  = &uart_input;

    ioinit ();

    /* loop forever, the interrupts are doing the rest */
    for (;;)  {         
        // sleep_mode();
        sleep_mode();
    }
    return (0);
}
