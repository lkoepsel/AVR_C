#include "sysclock.h"
#include "unolib.h"
#include "button.h"
#include <util/atomic.h>
#include <avr/interrupt.h>

volatile uint16_t sys_ctr_2 = 0;
volatile uint8_t bounce_delay = BOUNCE_DIVIDER;

extern button buttons[MAX_BUTTONS];

ISR (TIMER0_OVF_vect)      
{
    *PINport |= _BV(PINbit);
}

// Two versions for sysclock_2 ISR
// W/ SOFT_RESET: (best for boards which require a user-defined reset button)
/* ISR for sysclock_2
*  Provides millis() counter and debouncing of RESET and buttons
*  Number of buttons to check will slightly increase execution time of millis()
*/
#if SOFT_RESET
ISR (TIMER2_COMPA_vect)      
{

    sys_ctr_2++;

    //  X times divider for millis() otherwise buttons checked too often
    bounce_delay--;
    if (bounce_delay == 0) {
        if (is_RESET_pressed()) {
            soft_reset();
        }
        for (uint8_t i=0; i < MAX_BUTTONS; i++) {
            buttons[i].pressed = is_button_pressed(i);
        }
        bounce_delay = BOUNCE_DIVIDER;
    }
}
#endif

// W/o SOFT_RESET: (best for UNO and boards with a hardware RESET)
/* ISR for sysclock_2
*  Provides millis() counter and debouncing of buttons
*  Number of buttons to check will slightly increase execution time of millis()
*/
#if !SOFT_RESET
ISR (TIMER2_COMPA_vect)      
{

    sys_ctr_2++;

    //  X times divider for millis() otherwise buttons checked too often
    bounce_delay--;
    if (bounce_delay == 0) {
        for (uint8_t i=0; i < MAX_BUTTONS; i++) {
            buttons[i].pressed = is_button_pressed(i);
        }
        bounce_delay = BOUNCE_DIVIDER;
    }
}
#endif

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
}

void init_sysclock_2 (void)          
{
    /* Initialize timer 2
    * TCCR2A [ COM2A1 COM2A0 COM2B1 COM2B0 0 0 WGM21 WGM20 ] = 00000001
    * WGM22 WGM20 => PWM, Phase Correct, TOP = OCRA
    * TCCR2B [ FOC2A FOC2B 0 0 WGM22 CS22 CS21 CS20 ] = 00001011
    * CS22 CS20 => scalar of 32
    * Frequency = 16 x 10^6 / 32 / 255 = 2000Hz
    * -1 to account for overhead = 254
    * Counter performs another divide by 2 => 1000hz
    * Test using example/millis (delay(1000) = 999 ticks)
    */
    TCCR2A |= (_BV(WGM20));
    TCCR2B |= ( _BV(WGM22) | _BV(CS21) | _BV(CS20) ) ;
    OCR2A = 251;
    TIMSK2 |= _BV(OCIE2A);
    sei ();
}

#if SOFT_RESET
void init_RESET() {
    /* Use RESET_BUTTON as the pin for the reset button
    *  Change to actual value using define in unolib.h
    *  It is expected to be ACTIVE LOW and on PORT B
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
#endif
