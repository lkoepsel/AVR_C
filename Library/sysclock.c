#include "sysclock.h"
#include "unolib.h"
#include "button.h"
#include <util/atomic.h>
#include <avr/interrupt.h>

volatile uint16_t sys_ctr_0 = 0;
volatile uint16_t sys_ctr_1 = 0;
volatile uint16_t sys_ctr_2 = 0;

extern button buttons[max_buttons];

#if 1 // set to 1 to enable, conflicts with tone and RR_Scheduler
/* ISR for sysclock_0
* TC 0 setup for a 1MHz count, sys_ctr_0 tracks microseconds elapsed
*/
ISR (TIMER0_OVF_vect)      
{
    sys_ctr_0++;
}
#endif

/* ISR for sysclock_1
* 15ms of the delay is due to the button press checking in the ISR
* if button presses aren't required, comment out the code
*/
ISR (TIMER1_OVF_vect)      
{
    sys_ctr_1++;
}

/* ISR for sysclock_2
* 15ms of the delay is due to the button press checking in the ISR
* if button presses aren't required, comment out the code
*/
ISR (TIMER2_COMPA_vect)      
{
#if RESET_DEFINED
    if (is_RESET_pressed()) {
        soft_reset();
    }
#endif

    sys_ctr_2++;

    for (uint8_t i=0; i < max_buttons; i++) {
        buttons[i].pressed = is_button_pressed(i);
    }

}

uint16_t micros() {
    return(ticks() >> 4);
}

uint16_t ticks() {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        return(TCNT1);
    }
    return 0;
}

uint16_t millis() {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        return(sys_ctr_2);
    }
    return 0;   
}

void init_sysclock_0 (void)          
{
    /* Initialize timer 0
    * WGM02 WGM01 WGM00 => Fast PWM, TOP = OCRA
    * CS00 => scalar of 1
    * TCCR2A [ COM0A1 COM0A0 COM0B1 COM0B0 0 0 WGM01 WGM00 ] = 01000011
    * TCCR2B [ FOC0A FOC0B 0 0 WGM02 CS02 CS01 CS00 ] = 00001001
    * Frequency = 16 x 10^6 / 1 / OCRA + 1 = .5MHz @ OCRA = 15
    * Counter toggles every TOP (multiply by 2) => 1MHz
    * Test using example/millis (delay(1000) = 100000 ticks)
    */
    TCCR0A |= (_BV(COM0A0) | _BV(WGM00));
    TCCR0B |= ( _BV(WGM02) | _BV(CS01) ) ;
    OCR0A = 25;
    TIMSK0 |= _BV(TOIE0);
    DDRD |= _BV(PD6);

    sei ();
}

void init_sysclock_1 (void)          
{
    /* Initialize timer 1 as a free running clock at 16MHz
    * TCCR1A [ COM1A1 COM1A0 COM1B1 COM1B0 0 0 WGM11 WGM10 ] = 00000000
    * WGM13 WGM12 WGM11 WGM10 => Normal, TOP = 0xFFFF
    * TCCR2B [ ICNC1 ICES1 0 WGM13 CS12 CS12 CS11 CS10 ]
    * CS10 => scalar of 1
    * tick = 1/(16MHz) = 62.5ns or 62.5 x 10^-9s
    * Test using example/millis (delay(1)) = 16020 ticks
    * (16.020x10^3 ticks)x(62.5x10^-9 secs/tick) = 1.00125 x 10^-3 seconds
    */
    TCCR1A = 0;
    TCCR1B |= ( _BV(CS10));
    TIMSK1 |= (_BV(TOIE1));
    sei();
}

void init_sysclock_2 (void)          
{
    /* Initialize timer 2
    * TCCR2A [ COM2A1 COM2A0 COM2B1 COM2B0 0 0 WGM21 WGM20 ] = 00000001
    * WGM22 WGM20 => PWM, Phase Correct, TOP = OCRA
    * TCCR2B [ FOC2A FOC2B 0 0 WGM22 CS22 CS21 CS20 ]
    * CS22 CS20 => scalar of 32
    * Frequency = 16 x 10^6 / 32 / 255 = 2000Hz
    * -1 to account for overhead = 254
    * Counter performs another divide by 2 => 1000hz
    * Test using example/millis (delay(1000) = 999 ticks)
    */
    TCCR2A |= (_BV(WGM20));
    TCCR2B |= ( _BV(WGM22) | _BV(CS21) | _BV(CS20) ) ;
    OCR2A = 254;
    TIMSK2 |= _BV(OCIE2A);
    sei ();
}

void init_RESET() {
    /* Use RESET_BUTTON as the pin for the reset button
    *  Change to actual value using define in unolib.h
    *  It is expected to be ACTIVE LOW 
    */
    DDRB |= (_BV(RESET_BUTTON));
    PORTB |= (_BV(RESET_BUTTON));
}

uint8_t is_RESET_pressed(){

    static uint8_t reset_history = 0;
    uint8_t pressed = 0;    
 
    reset_history = reset_history << 1;
    reset_history |= read_RESET();

    if ((reset_history & RESET_MASK) == 0b00000111){ 
        pressed = 1;
        reset_history = 0b11111111;
    }
    return pressed;
}

uint8_t read_RESET() {

    return((PINB & (1 << RESET_BUTTON)) == 0);
}
