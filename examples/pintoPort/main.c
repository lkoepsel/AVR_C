// Simple conversion program to show Uno pin to ATmega328P port address and bit 
#include <stdio.h>
#include "uart.h"
#include "unolib.h"

int main(void) {    

    init_serial();
    puts("Testing pintoBit and pintoPort, enter an Uno Pin number (0-13)");
    puts("PORTB 0x23-25 and PORTD 0x29-2b");
    while(1) 
    {
        uint8_t Unopin;
        volatile uint8_t *PORTn = NULL;
        volatile uint8_t *PINn = NULL;
        scanf("%hhu",&Unopin);
        uint8_t bit = pintoBit(Unopin);
        PORTn = pintoPort(Unopin);
        PINn = PORTn;
        PINn--;
        PINn--;
        printf("Pin %d PINn Addr %p PORTn addr %p Bit %u\n",\
            Unopin, PINn, PORTn, bit);        
    }
        
    return 0;
}
