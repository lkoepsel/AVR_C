// avr_tog - uses AVR method of toggling a bit with digitalWrite()
#include "delay.h"
#include "pinMode.h"
#include "digitalWrite.h"

int LED = 3;
 
int main(void)
{
    /* set pin to output*/
    pinMode(LED, OUTPUT);

    while(1) 
    {
        /* toggle led on and off */
        digitalWrite(LED, TOG);
        delay(100);
    }
    return 0; 
}
