/*
* tone(uint8_t pin, uint16_t norw, uint8_t duration)
*/
#include "tone.h"
#include "delay.h"

volatile uint8_t *PINport;
volatile uint8_t *DDRport;
volatile uint8_t *PORTport;
volatile uint8_t PINbit;

/*
* frequencies for each note, freq = x per sec
* so can be used to time duration of note
*/
const uint16_t notes_freq[NUM_NOTES] PROGMEM = {
    31,
    33,
    35,
    37,
    39,
    41,
    44,
    46,
    49,
    52,
    55,
    58,
    62,
    65,
    69,
    73,
    78,
    82,
    87,
    93,
    98,
    104,
    110,
    117,
    123,
    131,
    139,
    147,
    156,
    165,
    175,
    185,
    196,
    208,
    220,
    233,
    247,
    262,
    277,
    294,
    311,
    330,
    349,
    370,
    392,
    415,
    440,
    466,
    494,
    523,
    554,
    587,
    622,
    659,
    698,
    740,
    784,
    831,
    880,
    932,
    988,
    1047,
    1109,
    1175,
    1245,
    1319,
    1397,
    1480,
    1568,
    1661,
    1760,
    1865,
    1976,
    2093,
    2217,
    2349,
    2489,
    2637,
    2794,
    2960,
    3136,
    3322,
    3520,
    3729,
    3951,
    4186,
    4435,
    4699,
    4978
};

/*
* scalars required for timer/counter 0
* for setting correct parameters for a given note
*/
const uint8_t notes_TCCR0B[NUM_NOTES] PROGMEM = {
    0x0D,
    0x0D,
    0x0D,
    0x0D,
    0x0D,
    0x0D,
    0x0D,
    0x0D,
    0x0D,
    0x0D,
    0x0D,
    0x0D,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A
} ;

/*
* counter value required for timer/counter 0
* for setting correct parameters for a given note
*/
const uint8_t notes_OCR0A[NUM_NOTES] PROGMEM = {
    126,
    118,
    112,
    106,
    100,
    95,
    89,
    85,
    80,
    75,
    71,
    67,
    252,
    240,
    226,
    214,
    200,
    191,
    180,
    168,
    159,
    150,
    142,
    134,
    127,
    119,
    112,
    106,
    100,
    95,
    89,
    84,
    80,
    75,
    71,
    67,
    253,
    239,
    226,
    213,
    201,
    189,
    179,
    169,
    159,
    151,
    142,
    134,
    127,
    120,
    113,
    106,
    100,
    95,
    90,
    84,
    80,
    75,
    71,
    67,
    63,
    60,
    56,
    53,
    50,
    47,
    45,
    42,
    40,
    38,
    36,
    34,
    253,
    239,
    226,
    213,
    201,
    190,
    179,
    169,
    159,
    151,
    142,
    134,
    127,
    119,
    113,
    106,
    100
};

/*
* scalars required for timer/counter 1
* for setting correct parameters for a given note
*/
const uint8_t notes_TCCR1B[NUM_NOTES] PROGMEM = {
    0x14,
    0x14,
    0x14,
    0x14,
    0x14,
    0x14,
    0x14,
    0x14,
    0x14,
    0x14,
    0x14,
    0x14,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x13,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12,
    0x12
} ;

/*
* counter value required for timer/counter 1
* for setting correct parameters for a given note
*/
const uint16_t notes_OCR1A[NUM_NOTES] PROGMEM = {
    504,
    473,
    446,
    422,
    401,
    381,
    355,
    340,
    319,
    300,
    284,
    269,
    1008,
    962,
    906,
    856,
    801,
    762,
    718,
    672,
    638,
    601,
    568,
    534,
    508,
    477,
    450,
    425,
    401,
    379,
    357,
    338,
    319,
    300,
    284,
    268,
    253,
    239,
    226,
    213,
    201,
    189,
    179,
    169,
    159,
    151,
    142,
    134,
    1012,
    956,
    903,
    852,
    804,
    759,
    716,
    676,
    638,
    602,
    568,
    536,
    506,
    478,
    451,
    426,
    402,
    379,
    358,
    338,
    319,
    301,
    284,
    268,
    253,
    239,
    226,
    213,
    201,
    190,
    179,
    169,
    159,
    151,
    142,
    134,
    127,
    119,
    113,
    106,
    100
};

void tone (uint8_t pin, uint8_t note, uint16_t duration)          
{

    if (note == 0) {
        noTone(pin);
        delay(duration);
    }
    else {
    
        /* Timer 0 is 8-bit PWM, PIN 7
        * COM0A1:0 =10 => Clear OC0A on Compare Match, set OC0A at BOTTOM
        * WGM02:0 = 101 => Phase Correct, TOP = OCRA
        * CS02:0 = clkI/O/value (Prescaler) found in notes
        * Set OCR0A value via notes
        */ 
        TCCR0A |=  _BV(COM0A1) | _BV(WGM00);
        TCCR0B = pgm_read_byte(&(notes_TCCR0B[note]));
        OCR0A = pgm_read_word(&(notes_OCR0A[note]));
    
        // UNO PINS 0-7 PORT D        
        if (pin <= 7) {
            PINport = &PIND;
            DDRport = &DDRD;
            PORTport = &PORTD;
            PINbit = pin;
        }

        // UNO PINS 8-13 PORT B        
        else if (pin <= 13) {
            PINport = &PINB;
            DDRport = &DDRB;
            PORTport = &PORTB;
            PINbit = pin - 8;
        }  

        // set port pin to be OUTPUT
        *DDRport |= _BV(PINbit);
    
        /* Enable timer 0 overflow interrupt and enable interrupts. */
        TIMSK0 = _BV (TOIE0);
        sei ();
        delay(duration);
        noTone(pin);
    }
    return;
}

void tone_on (uint8_t pin, uint8_t note)          
{

    if (note == 0) {
        noTone(pin);
    }
    else {
    
        /* Timer 0 is 8-bit PWM, PIN 7
        * COM0A1:0 =10 => Clear OC0A on Compare Match, set OC0A at BOTTOM
        * WGM02:0 = 101 => Phase Correct, TOP = OCRA
        * CS02:0 = clkI/O/value (Prescaler) found in notes
        * Set OCR0A value via notes
        */ 
        TCCR0A |=  _BV(COM0A1) | _BV(WGM00);
        TCCR0B = pgm_read_byte(&(notes_TCCR0B[note]));
        OCR0A = pgm_read_word(&(notes_OCR0A[note]));
    
        // UNO PINS 0-7 PORT D        
        if (pin <= 7) {
            PINport = &PIND;
            DDRport = &DDRD;
            PORTport = &PORTD;
            PINbit = pin;
        }

        // UNO PINS 8-13 PORT B        
        else if (pin <= 13) {
            PINport = &PINB;
            DDRport = &DDRB;
            PORTport = &PORTB;
            PINbit = pin - 8;
        }  

        // set port pin to be OUTPUT
        *DDRport |= _BV(PINbit);
    
        /* Enable timer 0 overflow interrupt and enable interrupts. */
        TIMSK0 = _BV (TOIE0);
        sei ();
    }
    return;
}

// for no tone on a pin, turn off interrupts and set pin LOW
void noTone(uint8_t pin) {
    TIMSK0 &= ~(_BV (TOIE0));
    *PORTport &= ~(_BV(PINbit));
}