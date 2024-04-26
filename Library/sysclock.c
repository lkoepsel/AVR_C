#include "sysclock.h"
#include "unolib.h"
#include "button.h"
#include <util/atomic.h>
#include <avr/interrupt.h>
#include "servo.h"

volatile uint16_t sys_ctr_0 = 0;
volatile uint16_t ticks_ro_ctr = 0;
volatile uint32_t sys_ctr_2 = 0;
volatile uint8_t bounce_delay = BOUNCE_DIVIDER;
volatile uint8_t iservo = 0;

#if TC3_RESET
volatile uint32_t sys_ctr_3 = 0;
#endif

extern servo servos[MAX_SERVOS];
extern button buttons[MAX_BUTTONS];

// Array to hold the task control blocks
// extern Task tasks[10];

// ****Defined Interrupt Service Routines****

// Required for tone, musical notes on a pin
// Enabled by tone(), tone_on() and no_tone in tone.c
// Conflicts with servo control code (pick one)
ISR (TIMER0_OVF_vect)      
{
    *PINport |= _BV(PINbit);
}

// Required for servo control, see examples/multi_servo
// Enabled by init_pulse_0() in sysclock.c
// Conflicts with tone control code (pick one)
ISR (TIMER0_COMPA_vect)      
{
    if (servos[iservo].state == HIGH) 
    {
        servos[iservo].high_count--;
        if (servos[iservo].high_count == 0)
        {
            servos[iservo].state = LOW;
            clr_bit(*servos[iservo].port, servos[iservo].bit);
            servos[iservo].high_count = servos[iservo].high_width;

        }
    }
    else
    {    
        servos[iservo].low_count--;
        if (servos[iservo].low_count == 0)
        {
            servos[iservo].state = HIGH;
            set_bit(*servos[iservo].port, servos[iservo].bit);
            servos[iservo].low_count = servos[iservo].low_width;
        }
    }
    iservo++;
    if (iservo == MAX_SERVOS)
    {
        iservo = 0;
    }
}

// Required for ticks timing, see examples/ticks
// Enabled by init_sysclock_1() in sysclock.c
ISR (TIMER1_OVF_vect)      
{
    ticks_ro_ctr++;
    // for (int i = 0; i < 10; i++) 
    // {
    //     if (tasks[i].function != NULL && tasks[i].previous_ticks > 0) 
    //     {
    //         tasks[i].previous_ticks--;
    //     }
    // }
}

// Software defined reset, for boards w/o hardware reset, i.e, xplainedmini
// Provides millis() counter and debouncing of RESET and buttons
//  Number of buttons to check will slightly increase execution time of millis()
ISR (TIMER2_COMPA_vect)      
{
    sys_ctr_2++;
    //  X times divider for millis() otherwise buttons checked too often
    bounce_delay--;
    if (bounce_delay == 0) {
        #if SOFT_RESET
        if (is_RESET_pressed()) {
            soft_reset();
        }
        #endif
        for (uint8_t i=0; i < MAX_BUTTONS; i++) {
            buttons[i].pressed = is_button_pressed(i);
        }
        bounce_delay = BOUNCE_DIVIDER;
    }
}

// TC3 defined reset, for boards w TC3 AND w/o hardware reset, i.e, xplainedmini
// Provides millis() counter and debouncing of RESET and buttons
//  Number of buttons to check will slightly increase execution time of millis()
#if TC3_RESET
ISR (TIMER3_COMPA_vect)      
{
    sys_ctr_3++;
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

// ****End of Defined Interrupt Service Routines****

// ****Defined Timer Setup Functions****

void init_pulse_0 (void)          
{
    // Initialize timer 0 for an PWM signal for servos
    // TCCR0A [ COM0A1 COM0A0 COM0B1 COM0B0 0 0 WGM01 WGM00 ] = 00000001
    // WGM02 WGM00 => PWM, Phase Correct, TOP = OCRA
    // TCCR0B [ FOC0A FOC0B 0 0 WGM02 CS02 CS01 CS00 ] = 00001001
    // CS00 => scalar of 1
    // Frequency = 16 x 10^6 / 1 / 255 = 2000Hz
    // Output Compare Match A Interrupt Enable -> TIMER0_COMPA_vect
    TCCR0A |=  _BV(COM0A1) | _BV(WGM01) | _BV(WGM00);
    TCCR0B |=  _BV(CS00);
    TIMSK0 |= _BV(OCIE0A);
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
    TCCR1B |= _BV(CS10);
    TIMSK1 |= _BV(TOIE1);
    sei();
}

void init_sysclock_2 (void)          
{
    // Initialize timer 2 for debouncing buttons and soft-defined reset
    // TCCR2A [ COM2A1 COM2A0 COM2B1 COM2B0 0 0 WGM21 WGM20 ] = 00000001
    // WGM22 WGM20 => PWM, Phase Correct, TOP = OCRA
    // TCCR2B [ FOC2A FOC2B 0 0 WGM22 CS22 CS21 CS20 ] = 00001011
    // CS22 CS20 => scalar of 32
    // Frequency = 16 x 10^6 / 32 / 255 = 2000Hz
    // Counter performs another divide by 2 => 1000hz
    // Test using example/millis (delay(1000) = 1000 ticks)
    // OCR2A value of 252 results in 1000
    TCCR2A |= (_BV(WGM20));
    TCCR2B |= ( _BV(WGM22) | _BV(CS21) | _BV(CS20) ) ;
    OCR2A = 252;
    TIMSK2 |= _BV(OCIE2A);
    sei ();
}

// Only available on ATmega328PB
#if TC3_RESET
void init_sysclock_3 (void)          
{
    // Initialize timer 3 for debouncing buttons and soft-defined reset
    // TCCR3A [ COM3A1 COM3A0 COM3B1 COM3B0 0 0 WGM31 WGM30 ] = 00000001
    // WGM33 WGM30 => PWM, Phase and Frequency Correct, TOP = OCR3A
    // TCCR2B [ INCNC3 ICES3 0 WGM33 CS33 CS31 CS30 ] = 00010001
    // CS30 => no prescaling
    // Frequency = 16 x 10^6 / 1 / 8063 = 2000Hz
    // Counter performs another divide by 2 => 1000hz
    // Test using example/millis (delay(1000) = 1000 ticks)
    TCCR3A = (_BV(WGM30));
    TCCR3B |= ( _BV(WGM33)  | _BV(CS30) );
    OCR3A = 8063;
    TIMSK3 |= _BV(OCIE3A);
    sei();
}
#endif

// ****End of Defined Timer Setup Functions****


uint16_t ticks(void) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        return(TCNT1);
    }
    return 0;
}

uint16_t ticks_ro(void) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        return(ticks_ro_ctr);
    }
    return 0;   
}

uint32_t millis(void) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        return(sys_ctr_2);
    }
    return 0;   
}

#if TC3_RESET
uint32_t millis_TC3(void) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        return(sys_ctr_3);
    }
    return 0;   
}
#endif

// Routines required for software defined reset
#if SOFT_RESET
void init_RESET(void) {
    /* Use RESET_BUTTON as the pin for the reset button
    *  Change to actual value using define in unolib.h
    *  It is expected to be ACTIVE LOW and on PORT B
    */
    DDRB |= (_BV(RESET_BUTTON));
    PORTB |= (_BV(RESET_BUTTON));
}

uint8_t is_RESET_pressed(void){

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

uint8_t read_RESET(void) {

    return((PINB & (1 << RESET_BUTTON)) == 0);
}
#endif

// Routines required for software defined reset
#if TC3_RESET
void init_RESET(void) {
    /* Use RESET_BUTTON as the pin for the reset button
    *  Change to actual value using define in unolib.h
    *  It is expected to be ACTIVE LOW and on PORT B
    */
    DDRB |= (_BV(RESET_BUTTON));
    PORTB |= (_BV(RESET_BUTTON));
}

uint8_t is_RESET_pressed(void){

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

uint8_t read_RESET(void) {

    return((PINB & (1 << RESET_BUTTON)) == 0);
}
#endif
