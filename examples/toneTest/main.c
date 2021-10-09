/*
* toneTest() - very simple test to test a tone
* requires an oscilloscope to see freq on the pin
*/
#include <avr/sleep.h>
#include "tone.h"
#include "avr_uno.h"


int main (void)
{

    while (1) {
        tone(8, NOTE_F7);
        sleep_mode();
    }
    return (0);
}
