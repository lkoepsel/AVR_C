#include "unolib.h"
#include "pinMode.h"
#include "digitalWrite.h"
#include "delay.h"
#include "avr8-stub.h"

#define BLINK_DELAY_MS 500
 
int main(void)
{
    debug_init();
    uint8_t LED = 13;
    /* set LED to output*/
    pinMode(LED, OUTPUT);
    sei();

    while(1) {
        /* toggle led on and off */
        digitalWrite(LED, TOG);
        delay(BLINK_DELAY_MS);
    }
    return(0); 
}
