#include "avr_uno.h"
#include "pinMode.h"
#include "digitalWrite.h"
#include "delay.h"
 
#define BLINK_DELAY_MS 500
 
int main(void)
{
    uint8_t LED = 13;
    /* set LED to output*/
    pinMode(LED, OUTPUT);

    while(1) {
        /* turn led on */
        digitalWrite(LED, TOG);
        delay(BLINK_DELAY_MS);
    }
    return(0); 
}
