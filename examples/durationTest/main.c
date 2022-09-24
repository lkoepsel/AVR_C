// durationTest() - very simple linear test to demonstrate playing a melody
// requires a speaker to hear the melody on the pin
// connect positive speaker wire to pin 8
// connect negative speaker wire to center pin of potentiometer
// connect either remaining lead of potentiometer to GND

#include "tone.h"
#include "delay.h"

int main (void)
{
    const uint8_t musicPin = 8;

    tone(musicPin, NOTE_C4, quarter);
    delay(d16);

    tone(musicPin, NOTE_G3, eighth);
    delay(d16);

    tone(musicPin, NOTE_G3, eighth);
    delay(d16);

    tone(musicPin, NOTE_A3, quarter);
    delay(d8);

    tone(musicPin, NOTE_G3, quarter);
    delay(d8);

    tone(musicPin, 0, quarter);
    delay(d8);

    tone(musicPin, NOTE_B3, d_quarter);
    delay(d8);

    tone(musicPin, NOTE_C4, d_quarter);
    delay(d8);

    return 0;
}
