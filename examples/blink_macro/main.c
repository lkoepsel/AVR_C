// avr_macro - uses bit setting by address similar to blink_avr
// The difference is using the macros set_bit(port,bit) and clr_bit(port,bit)
#include <delay.h>
#include <avr/io.h>
#include "unolib.h"

int main(void)
{
    // Setup two variables which will track the port to be manipulated (B or D)
    volatile uint8_t *PORTn;
    volatile uint8_t *DDRn;

    // pintoBit/Port provide the translation of Uno pin to specific port
    uint8_t bit = pintoBit(LED_BUILTIN);
    PORTn = pintoPort(LED_BUILTIN);
    DDRn = PORTn;

    // the DDRn address is right below PORTn address, set bit to make OUTPUT
    DDRn--;
    set_bit(*DDRn, bit);

    while(1) 
    {
        // setting a PORTn bit will make the pin HIGH
        set_bit(*PORTn, bit);
        _delay_ms(1000);
        // clearing a PORTn bit will make the pin LOW
        clr_bit(*PORTn, bit);
        _delay_ms(1000);
    }
    return 0; 
}
