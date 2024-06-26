#include "unolib.h"
#include "pinMode.h"
#include "digitalWrite.h"
#include "delay.h"
 
int main(void)
{
    // use built-in led and set to output
    pinMode(LED_BUILTIN, OUTPUT);
    int delay_ms = 200;

    while(1) 
    {
        // toggle led on and off
        digitalWrite(LED_BUILTIN, HIGH);
        delay(delay_ms);
        digitalWrite(LED_BUILTIN, LOW);
        delay(delay_ms);
    }
    return 0; 
}
