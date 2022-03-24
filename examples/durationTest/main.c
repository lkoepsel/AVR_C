/*
* durationTest() - very simple linear test to test a tone duration
* requires a speaker to hear the melody on the pin
* connect positive speaker wire to pin
* connect negative speaker wire to ~10uF capacitor
* connect remaining lead of capacitor to GND
*/
#include "tone.h"
#include "unolib.h"
#include "delay.h"

int main (void)
{
    const uint8_t musicPin = 11;

    while(1) 
    {
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
