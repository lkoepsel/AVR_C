/*
* durationTest() - very simple test to test a tone duration
* requires a speaker to hear the melody on the pin
*/
#include "tone.h"
#include "unolib.h"
#include "delay.h"

int main (void)
{
    uint8_t musicPin = 12;
    pinMode(13, OUTPUT);

    while(1) {
        tone(musicPin, NOTE_C4, d4);
        noTone(musicPin);
        delay(internote);
    
        tone(musicPin, NOTE_G3, d8);
        noTone(musicPin);
        delay(internote);
    
        tone(musicPin, NOTE_G3, d8);
        noTone(musicPin);
        delay(internote);
    
        tone(musicPin, NOTE_A3, d4);
        noTone(musicPin);
        delay(internote);
    
        tone(musicPin, NOTE_G3, d4);
        noTone(musicPin);
        delay(internote);
    
        tone(musicPin, 0, d4);
        noTone(musicPin);
        delay(internote);
    
        tone(musicPin, NOTE_B3, d4);
        noTone(musicPin);
        delay(internote);
    
        tone(musicPin, NOTE_C4, d4);
        noTone(musicPin);
        delay(internote);
    }
    return (0);
}
