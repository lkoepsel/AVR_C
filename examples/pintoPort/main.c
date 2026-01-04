// Simple conversion program to show Uno pin to ATmega328P port address and bit 
#include <stdio.h>
#include "uart.h"
#include "unolib.h"

void valid(uint8_t p, char c)
{
    volatile uint8_t *PORTn = NULL;
    volatile uint8_t *PINn = NULL;

    uint8_t bit = pintoBit(p);
    PORTn = pintoPort(p);
    PINn = PORTn;
    PINn--;
    PINn--;
    printf("Pin %d PIN%c %p PORT%c %p Bit %u\n",\
        p, c, PINn, c, PORTn, bit);        
}

int main(void) {    

    init_serial();
    puts("Testing pintoBit and pintoPort, enter an Uno Pin number (0-13)");
    puts("PORTB 0x23-25 and PORTD 0x29-2b");
    char port = 'x';
    while(1)
    {
        int c = getchar();

        // Skip carriage returns and newlines when nothing has been entered
        if (c == '\n' || c == '\r')
        {
            continue;
        }

        // Check if it's a digit
        if (c >= '0' && c <= '9')
        {
            uint8_t Unopin = c - '0';

            // Check for second digit (peek ahead)
            int next = getchar();
            if (next >= '0' && next <= '9')
            {
                Unopin = Unopin * 10 + (next - '0');
            }

            // Clear to end of line (consume '\r' and '\n')
            while (next != '\n' && next != '\r' && next != EOF)
            {
                next = getchar();
            }

            if (Unopin <= 7)
            {
                port = 'D';
                valid(Unopin, port);
            }
            else if (Unopin <= 13)
            {
                port = 'B';
                valid(Unopin, port);
            }
            else
            {
                printf("Invalid entry %u\n", Unopin);
            }
        }
        else
        {
            // Invalid input - clear rest of line
            int temp = getchar();
            while (temp != '\n' && temp != '\r' && temp != EOF)
            {
                temp = getchar();
            }
            printf("Invalid entry %c\n", c);
        }
    }

    return 0;
}
