/*
* durationTest() - very simple test to test a tone duration
* requires an oscilloscope to see freq on the pin
* tone requires a delay to account for the note time and desired silence
*/
#include "tone.h"
#include "avr_uno.h"
#include "delay.h"

int main (void)
{
    uint8_t musicPin = 2;
    pinMode(13, OUTPUT);

    while(1) {
        tone(musicPin, NOTE_C4);
        notone(musicPin);
        delay(31250/2);
        digitalWrite(13, TOG);
        // notone(musicPin);        
        // delay(31250/16);
    
        // tone(musicPin, NOTE_G3);
        // delay(d8);
        // notone(musicPin);
        // delay(internote);
    
        // tone(musicPin, NOTE_G3);
        // delay(d8);
        // notone(musicPin);
        // delay(internote);
    
        // tone(musicPin, NOTE_A3);
        // delay(d4);
        // notone(musicPin);
        // delay(internote);
    
        // tone(musicPin, NOTE_G3);
        // delay(d4);
        // notone(musicPin);
        // delay(internote);
    
        // tone(musicPin, 0);
        // delay(d4);
        // notone(musicPin);
        // delay(internote);
    
        // tone(musicPin, NOTE_B3);
        // delay(d4);
        // notone(musicPin);
        // delay(internote);
    
        // tone(musicPin, NOTE_C4);
        // delay(d4);
        // notone(musicPin);
        // delay(internote);
    }
    return (0);
}
