#include "sysclock.h"
#include "unolib.h"
#include "button.h"
#include <util/atomic.h>
#include <avr/interrupt.h>


volatile uint16_t sys_ctr_0 = 0;
volatile uint16_t sys_ctr_1 = 0;
volatile uint16_t sys_ctr_2 = 0;
volatile uint16_t ctr_copy = 0;

extern button buttons[max_buttons];

/* ISR for sysclock_0
* TC 0 setup for a 1MHz count, sys_ctr_0 tracks microseconds elapsed
*/
ISR (TIMER0_COMPA_vect)      
{
    sys_ctr_0++;
    PIND |= _BV(PD2);
}

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
    if (is_RESET_pressed()) {
        soft_reset();
    }

    sys_ctr_2++;

    for (int i = 0; i < max_buttons; i++) {
        buttons[i].pressed = is_button_pressed(i);
    }

}

uint16_t micros() {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
    ctr_copy = TCNT1;
    }
    return(ctr_copy);
}

uint16_t millis() {

      return(sys_ctr_2);
}

void init_sysclock_0 (void)          
{
    /* Initialize timer 0
    * TCCR2A [ COM0A1 COM0A0 COM0B1 COM0B0 0 0 WGM01 WGM00 ] = 00000011
    * WGM02 WGM01 WGM00 => Fast PWM, TOP = OCRA
    * TCCR2B [ FOC0A FOC0B 0 0 WGM02 CS02 CS01 CS00 ]
    * CS00 => scalar of 1
    * Frequency = 16 x 10^6 / 1 / 8 = 2MHz
    * Counter performs another divide by 2 => 1MHz
    * Test using example/millis (delay(1000) = 100000 ticks)
    */
    TCCR0A |= (_BV(COM0A0) | _BV(WGM00) | _BV(WGM00));
    TCCR0B |= ( _BV(WGM02) | _BV(CS00) ) ;
    OCR0A = 4;
    TIMSK0 |= _BV(OCIE0A);
    DDRD |= (_BV(PD2) | _BV(PD6));

    sei ();
}

void init_sysclock_1 (void)          
{
    /* Initialize timer 2
    * TCCR1A [ COM1A1 COM1A0 COM1B1 COM1B0 0 0 WGM11 WGM10 ] = 00000000
    * WGM13 WGM12 WGM11 WGM10 => Normal, TOP = 0xFFFF
    * TCCR2B [ ICNC1 ICES1 0 WGM13 CS12 CS12 CS11 CS10 ]
    * CS11 => scalar of 8
    * Frequency = 16 x 10^6 / 1 / 40 = 50kHz
    * -1 to account for overhead = 39
    * Counter performs another divide by 2 => 25kHz
    * Test using example/millis (delay(1000) = 40527 ticks)
    */
    TCCR1A = 0;
    TCCR1B |= ( _BV(CS11));
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
    /* Use RESET_BUTTON as the pin for the reset button
    *  Change to actual value using define in unolib.h
    *  It is expected to be ACTIVE LOW 
    */
    DDRB |= (_BV(RESET_BUTTON));
    PORTB |= (_BV(RESET_BUTTON));
    sei ();
}

uint8_t is_RESET_pressed(){

    static uint8_t reset_history = 0;
    uint8_t pressed = 0;    
 
    reset_history = reset_history << 1;
    reset_history |= read_RESET();

    if ((reset_history & RESET_MASK) == 0b11000111){ 
        pressed = 1;
        reset_history = 0b11111111;
    }
    return pressed;
}

uint8_t read_RESET() {

    return((PINB & (1 << RESET_BUTTON)) == 0);
}
