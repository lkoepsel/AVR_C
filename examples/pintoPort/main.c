// Simple conversion program to show Uno pin to ATmega328P port address and bit
// The PSTR() macro stores the string in program memory, 
//  and printf_P() reads format strings from program memory instead of RAM.
#include <stdio.h>
#include <avr/pgmspace.h>
#include "uart.h"
#include "unolib.h"

// Clear input buffer to end of line
static void clear_eol(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != '\r' && c != EOF);
}

void valid(uint8_t p, char c)
{
    volatile uint8_t *PORTn = pintoPort(p);
    volatile uint8_t *PINn = PORTn - 2;  // PIN is 2 addresses below PORT

    printf_P(PSTR("Pin %d PIN%c %p PORT%c %p Bit %u\n"),
        p, c, PINn, c, PORTn, pintoBit(p));
}

int main(void) {

    init_serial();
    printf_P(PSTR("Testing pintoBit and pintoPort, enter Uno Pin (0-13)\nPORTB 0x23-25 PORTD 0x29-2b\n"));

    while(1)
    {
        int c = getchar();

        if (c == '\n' || c == '\r') continue;

        if (c >= '0' && c <= '9')
        {
            uint8_t pin = c - '0';
            int next = getchar();

            if (next >= '0' && next <= '9')
            {
                pin = pin * 10 + (next - '0');
                next = getchar();
            }

            // Clear remaining input
            if (next != '\n' && next != '\r') clear_eol();

            if (pin <= 13)
            {
                valid(pin, (pin <= 7) ? 'D' : 'B');
            }
            else
            {
                printf_P(PSTR("Invalid: %u\n"), pin);
            }
        }
        else
        {
            clear_eol();
            printf_P(PSTR("Invalid: %c\n"), c);
        }
    }

    return 0;
}
