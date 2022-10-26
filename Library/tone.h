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
* Uses notes a file containing one set of definitions and two single dimension arrays:
*   definitions: notes as offsets into the arrays
*   notes_TCCR1B: scalar settings for a specific note, 
*   notes_OCR1A:  timer counter value req'd for a specific note
*/

#ifndef TONE_H
#define TONE_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include "sysclock.h"
#include "digitalWrite.h"

extern volatile uint8_t *PINport;
extern volatile uint8_t *DDRport;
extern volatile uint8_t *PORTport;
extern volatile uint8_t PINbit;

void tone (uint8_t pin, uint8_t note, uint16_t duration);       
void tone_on (uint8_t pin, uint8_t note);
void noTone(uint8_t pin);

/* note duration delay values, must be used after every note in (tone)
*/
#define d1 1000
#define d2 500
#define d4 250
#define d8 125
#define d16 63
#define internote 125

#define whole d1
#define half d2
#define quarter d4
#define eighth d8
#define sixteenth d16

#define d_whole d1+d1/2
#define d_half d2+d2/2
#define d_quarter d4+d4/2
#define d_eighth d8+d8/2
#define d_sixteenth d16+d16/2

/*
* offsets required for timer/counters 
* for setting correct parameters for a given note
*/
#define NOTE_B0  0
#define NOTE_C1  1
#define NOTE_CS1 2
#define NOTE_D1  3
#define NOTE_DS1 4
#define NOTE_E1  5
#define NOTE_F1  6
#define NOTE_FS1 7
#define NOTE_G1  8
#define NOTE_GS1 9
#define NOTE_A1  10
#define NOTE_AS1 11
#define NOTE_B1  12
#define NOTE_C2  13
#define NOTE_CS2 14
#define NOTE_D2  15
#define NOTE_DS2 16
#define NOTE_E2  17
#define NOTE_F2  18
#define NOTE_FS2 19
#define NOTE_G2  20
#define NOTE_GS2 21
#define NOTE_A2  22
#define NOTE_AS2 23
#define NOTE_B2  24
#define NOTE_C3  25
#define NOTE_CS3 26
#define NOTE_D3  27
#define NOTE_DS3 28
#define NOTE_E3  29
#define NOTE_F3  30
#define NOTE_FS3 31
#define NOTE_G3  32
#define NOTE_GS3 33
#define NOTE_A3  34
#define NOTE_AS3 35
#define NOTE_B3  36
#define NOTE_C4  37
#define NOTE_CS4 38
#define NOTE_D4  39
#define NOTE_DS4 40
#define NOTE_E4  41
#define NOTE_F4  42
#define NOTE_FS4 43
#define NOTE_G4  44
#define NOTE_GS4 45
#define NOTE_A4  46
#define NOTE_AS4 47
#define NOTE_B4  48
#define NOTE_C5  49
#define NOTE_CS5 50
#define NOTE_D5  51
#define NOTE_DS5 52
#define NOTE_E5  53
#define NOTE_F5  54
#define NOTE_FS5 55
#define NOTE_G5  56
#define NOTE_GS5 57
#define NOTE_A5  58
#define NOTE_AS5 59
#define NOTE_B5  60
#define NOTE_C6  61
#define NOTE_CS6 62
#define NOTE_D6  63
#define NOTE_DS6 64
#define NOTE_E6  65
#define NOTE_F6  66
#define NOTE_FS6 67
#define NOTE_G6  68
#define NOTE_GS6 69
#define NOTE_A6  70
#define NOTE_AS6 71
#define NOTE_B6  72
#define NOTE_C7  73
#define NOTE_CS7 74
#define NOTE_D7  75
#define NOTE_DS7 76
#define NOTE_E7  77
#define NOTE_F7  78
#define NOTE_FS7 79
#define NOTE_G7  80
#define NOTE_GS7 81
#define NOTE_A7  82
#define NOTE_AS7 83
#define NOTE_B7  84
#define NOTE_C8  85
#define NOTE_CS8 86
#define NOTE_D8  87
#define NOTE_DS8 88
// set the size of the notes arrays, based on max offset + 1
#define NUM_NOTES NOTE_DS8 + 1
#endif