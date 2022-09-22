/*

  Melody

  Plays a melody

  circuit:

  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010

  modified 30 Aug 2011

  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone

* requires a speaker to hear the melody on the pin
* connect positive speaker wire to pin
* connect negative speaker wire to ~10uF capacitor
* connect remaining lead of capacitor to GND
*/

#include "tone.h"
#include "unolib.h"
#include "delay.h"


int main() {

    uint8_t musicPin = 11;

    // notes in the melody:
    int melody[] = 
    {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
    };

    // note durations: 4 = quarter note, 8 = eighth note, etc.:
    int noteDurations[] = 
    {
    d4, d8, d8, d4, d4, d4, d4, d4
    };

    // iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < 8; thisNote++) {

      // note duration is pre-calculated and defined using a "d"
      //e.g. quarter note = d4, eighth note = d8, etc.
      tone(musicPin, melody[thisNote], noteDurations[thisNote]);

      // to distinguish the notes, set a minimum time between them.
      // in this case, divide the notes duration by 4
      int pauseBetweenNotes = (noteDurations[thisNote] >> 2);

      delay(pauseBetweenNotes);

      // stop the tone playing:
      noTone(musicPin);

    }
}
