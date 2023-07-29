// avr_tog - uses AVR method of toggling a bit with digitalWrite()
#include "delay.h"
#include "pinMode.h"
#include "digitalWrite.h"

int main(void)
{
    /* set pin to output*/
    pinMode(LED_BUILTIN, OUTPUT);

    while(1) 
    {
        /* toggle led on and off */
        digitalWrite(LED_BUILTIN, TOG);
        delay(1000);
    }
    return 0; 
}
