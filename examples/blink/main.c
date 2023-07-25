#include "unolib.h"
#include "pinMode.h"
#include "digitalWrite.h"
#include "delay.h"
 
int main(void)
{
    // use built-in led and set to output
    pinMode(LED_BUILTIN, OUTPUT);

    while(1) 
    {
        // toggle led on and off
        digitalWrite(LED_BUILTIN, TOG);
        // delay(1);
        // digitalWrite(LED_BUILTIN, LOW);
        // delay(1);
    }
    return 0; 
}
