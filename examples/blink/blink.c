#include "avr_uno.h"
#include "pinMode.h"
#include "digitalWrite.h"
 
#define BLINK_DELAY_MS 500
 
int main(void)
{
    uint8_t LED = 13;
    /* set LED to output*/
    pinMode(LED, OUTPUT);

    while(1) {
        /* turn led on */
        digitalWrite(LED, HIGH);
        _delay_ms(BLINK_DELAY_MS);

        /* turn led off */
        digitalWrite(LED, LOW);
        _delay_ms(BLINK_DELAY_MS);
    }
    return(0); 
}
