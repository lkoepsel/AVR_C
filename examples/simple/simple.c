/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <joerg@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.        Joerg Wunsch
 * ----------------------------------------------------------------------------
 *
 * Simple AVR demonstration.  Controls a LED that can be directly
 * connected from OC1/OC1A to GND.  The brightness of the LED is
 * controlled with the PWM.  After each period of the PWM, the PWM
 * value is either incremented or decremented, that's all.
 *
 * $Id: group__demo__project.html,v 1.1.1.24 2016/02/09 07:13:43 joerg_wunsch Exp $
 * UPDATE: Lief Koepsel www.wellys.com 9/27/21
 * 1. iocompat.h missing ATmega328p, removed it in order to ease debugging
 * 2. Manually set parameters, per ATmega328P register req'ts
 * 3. Changed variable named pwm to duty_cycle, as it more accurately describes its context
 * 3. For every interrupt, the duty cycle will be incr or decr (easy to see on a scope)
 * 4. Removed extraneous code not specific to ATmeg328P
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define TIMER1_TOP 1023   /* 10-bit PWM */

enum { UP, DOWN };

ISR (TIMER1_OVF_vect)       /* Note [2] */
{
    static uint16_t duty_cycle;    /* Note [3] */
    static uint8_t direction;
    switch (direction)      /* Note [4] */
    {
        case UP:
            if (++duty_cycle == TIMER1_TOP)
                direction = DOWN;
            break;
        case DOWN:
            if (--duty_cycle == 0)
                direction = UP;
            break;
    }
    OCR1A = duty_cycle;          /* Note [5] */
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
     */
    TCCR1B |= _BV(CS11) | _BV(CS10);
    /*
     * Run any device-dependent timer 1 setup hook if present.
     */
    /* Set PWM value to 0. */
    OCR1A = 0;
    /* Enable OC1 as output. */
    DDRB = _BV (PB1);
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
