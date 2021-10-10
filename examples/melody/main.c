/*
* toneTest()
*/
#include "tone.h"
#include "avr_uno.h"
#include "delay.h"


int main (void)
{
    uint8_t musicPin = 2;
    // notes in the melody:
    int melody[] = {

      NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
    };

    // note durations: 4 = quarter note, 8 = eighth note, etc.:
    int noteDuration[] = {

      4, 8, 8, 4, 4, 4, 4, 4
    };

    int noteDelay[] = {

      d4, d8, d8, d4, d4, d4, d4, d4
    };


    /* loop forever, the interrupts are doing the rest */
    while (1)  {         

        for (int thisNote = 0; thisNote < 8; thisNote++) {

        tone(musicPin, melody[thisNote], noteDuration[thisNote]);
        delay(noteDelay[thisNote]);
        tone(musicPin, 0, d8);
        delay(internote);

        }
        delay(1000);
    }
    return (0);
}
