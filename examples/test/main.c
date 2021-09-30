#include "avr_uno.h"
#include "pinMode.h"
#include "digitalWrite.h"
 
#define BLINK_DELAY_MS 500
 
int main(void)
{
    uint8_t LED = 13;
    /* set LED to output*/
    pinMode(LED, OUTPUT);

    for (int i=0;i<10;i++) {
        /* turn led on */
        on_led();
        _delay_ms(BLINK_DELAY_MS);
        off_led();
        _delay_ms(BLINK_DELAY_MS);
    }
    return(0); 
}
