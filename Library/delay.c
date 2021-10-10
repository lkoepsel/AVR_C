#include "delay.h"

ISR (TIMER1_OVF_vect)      
{
    digitalWrite(8, TOG);
    count1 += 1;
}

void initT1 (void)          
{
    /* Timer 1 is 10-bit PWM 
    * TCCR1A = TIMER1_PWM_INIT;
    * COM1A1:0 =10 => Clear OC1A/OC1B on Compare Match when up-counting */
    TCCR1A |=  _BV(COM1A1) | _BV(WGM11) | _BV(WGM10);

    /* * Start timer 1.
    * CS12:0 = 011 => clkI/O/8 (From prescaler)
    * WGM13:0 = 1011 => PWM, Phase Correct, TOP = OCR1A */
    TCCR1B = 0x12;

    /* Set PWM value to 624 => 16MHz / 64 / 624 = 400
    *  Phase Correct timer divides by 2 => 200Hz 
    *  Pin toggle divides by 2 as well => 100Hz at Pin */
    OCR1A = 500;

    /* Set up pin for signal */
    pinMode(8, OUTPUT);

    /* Enable timer 1 overflow interrupt and enable interrupts. */
    TIMSK1 = _BV (TOIE1);
    sei ();
}

uint8_t delay(uint16_t ms) {
    initT1 ();
    uint16_t previousCount = count1;

    while(1) {
        if (count1 - previousCount >= ms) {
            return(0);
        }
    }
}
