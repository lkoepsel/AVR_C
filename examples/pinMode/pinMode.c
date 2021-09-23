#include "avr_uno.h"
#include "pinMode.h"
#include "digitalWrite.h"

#define BLINK_DELAY_MS 50

uint16_t main (void)
{
    uint8_t UNO_pin = 13;
    on_led();
    pinMode(UNO_pin, OUTPUT);
    for (uint8_t i=0;i<40;i++) {
        digitalWrite(UNO_pin, HIGH);
        _delay_ms(BLINK_DELAY_MS);
        digitalWrite(UNO_pin, LOW);
        _delay_ms(BLINK_DELAY_MS);
        off_led();
    }
}
