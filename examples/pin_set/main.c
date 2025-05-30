// pin_set - Use the serial port to toggle a pin or set a clock
// Requires serial monitor set to 250000, 8, 1, None with no line ending
// Use Arduino Serial Monitor, minicom, PUTTY or your favorite serial monitor
 
#include <stdio.h>
#include "analogWrite.h"
#include "digitalWrite.h"
#include "pinMode.h"
#include "uart.h"

#define NTASKS 4


// Uno pin numbers
#define LED0 2
#define LED1 3
#define LED2 4
#define CLOCK 5


uint8_t state0 = LOW;
uint8_t state1 = LOW;
uint8_t state2 = LOW;
uint8_t clock_dc = 0;

void zero (void) {
    /* toggle led on and off */
    state0 = !state0;
    digitalWrite(LED0, state0);
    return;
} 

void one (void) {
    /* toggle led on and off */
    state1 = !state1;
    digitalWrite(LED1, state1);
    return;
} 

void two (void) {
    /* toggle led on and off */
    state2 = !state2;
    digitalWrite(LED2, state2);
    return;
} 

void clock(void) 
{
    printf("3_Clock_dc %d\n", clock_dc);
    if (clock_dc == 0)
    {
        clock_dc = 127; // 50% duty cycle
    }
    else
    {
        // Set the built-in LED PB5 to be an output
        DDRB |= _BV(DDB5);
        PORTB &= ~(_BV(PORTB5));
        clock_dc = 0; // 0% duty cycle
    }
    // Set the clock pin to the new duty cycle
    printf("4_Clock_dc %d\n", clock_dc);
    analogWrite(CLOCK, clock_dc);
}

void (*tasklist[NTASKS])() = {zero, one, two, clock};

int main(void)
{
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    while (1)
    {
        init_serial();
        clear_all_TC();
        char input;

        puts("Pin Set");
        while((input = getchar())!= EOF) 
        {
            putchar(input);
            if (input == 'c' || input == 'C') 
            {
                printf("0_Clock_dc %d\n", clock_dc);
                tasklist[3]();
                printf("1_Clock_dc %d\n", clock_dc);
            }
            else if (input == '0') 
            {
                tasklist[0]();
            }
            else if (input == '1') 
            {
                tasklist[1]();
            }
            else if (input == '2') 
            {
                tasklist[2]();
            }
            else if (input == 'q' || input == 'Q')  
            {
                puts("\nExiting program.");
                break;
            }
            else 
            {
                puts("\nType 0-2, c or q to quit.");
            }
        }
    }
    return 0; 
}
