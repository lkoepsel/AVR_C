#include "avr_uno.h"
#include "pinMode.h"
#include "digitalWrite.h"
 
#define BLINK_DELAY_MS 500
 
int main(void)
{
    struct bank
    {
        uint8_t l1;
        uint8_t l2;
        uint8_t l3;
    };

    struct bank 
    uint8_t LED = 13;
    uint8_t LED = 13;
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
