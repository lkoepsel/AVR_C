// melody_array - plays a melody from an array
// requires a speaker to hear the melody on the pin
// connect positive speaker wire to pin
// connect negative speaker wire center pin of pot
// connect either remaining lead of pot to GND
// Uses songs from: https://github.com/robsoncouto/arduino-songs
// Replace all 2,4,8,16 values with half, quarter, eighth or sixteenth, respectively
// Replace all negative values with a "d_" and the note, as in "-2" == "d_half"

#include <stdlib.h>
#include "delay.h"
#include "tone.h"

int main() {

    uint8_t musicPin = 8;

    // notes in the melody:
    int melody[] = 
    {
      NOTE_C4,quarter, NOTE_C4,eighth, 
      NOTE_D4,d_quarter, NOTE_C4,d_quarter, NOTE_F4,d_quarter,
      NOTE_E4,d_half, NOTE_C4,quarter, NOTE_C4,eighth, 
      NOTE_D4,d_quarter, NOTE_C4,d_quarter, NOTE_G4,d_quarter,
      NOTE_F4,d_half, NOTE_C4,quarter, NOTE_C4,eighth,

      NOTE_C5,d_quarter, NOTE_A4,d_quarter, NOTE_F4,d_quarter, 
      NOTE_E4,d_quarter, NOTE_D4,d_quarter, NOTE_AS4,quarter, NOTE_AS4,eighth,
      NOTE_A4,d_quarter, NOTE_F4,d_quarter, NOTE_G4,d_quarter,
      NOTE_F4,d_half,
    };

    // iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < sizeof(melody)/sizeof(melody[0]); thisNote += 2) 
    {
      tone(musicPin, melody[thisNote], melody[thisNote+1]);
      // to distinguish the notes, set a minimum time between them.
      // in this case, divide the notes duration by 4
      int pauseBetweenNotes = (melody[thisNote+1] >> 2);
      delay(pauseBetweenNotes);
    }
}
