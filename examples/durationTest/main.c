/*
* durationTest() - very simple test to test a tone duration
* requires an oscilloscope to see freq on the pin
* duration can be:
* 0 - continue until another tone or notone called
* 2,4,8,16 - half, quarter, eighth or sixteenth notes
* tone requires a delay to account for the note time and desired silence
*/
#include "tone.h"
#include "avr_uno.h"

int main (void)
{

    tone(8, NOTE_C4, 4);
    delay(d4);
    notone(8);
    delay(internote);

    tone(8, NOTE_G3, 4);
    delay(d8);
    notone(8);
    delay(internote);

    tone(8, NOTE_G3, 4);
    delay(d8);
    notone(8);
    delay(internote);

    tone(8, NOTE_A3, 4);
    delay(d4);
    notone(8);
    delay(internote);

    tone(8, NOTE_G3, 4);
    delay(d4);
    notone(8);
    delay(internote);

    tone(8, 0, 4);
    delay(d4);
    notone(8);
    delay(internote);

    tone(8, NOTE_B3, 4);
    delay(d4);
    notone(8);
    delay(internote);

    tone(8, NOTE_C4, 4);
    delay(d4);
    notone(8);
    delay(internote);


    return (0);
}
