#include "main.h"
#include "uart.h"

/* Put your global variables here */
// state contains the current state of the FSM
uint8_t state = 0;

uint8_t LED_bit0 = 4;
uint8_t LED_bit1 = 3;
uint8_t BLUE_LED = 6;

/* Main */ 
int main() {

   init_serial();
   pinMode(LED_bit0, OUTPUT);
   pinMode(LED_bit1, OUTPUT);

   buttons[UP].uno = 9;
   pinMode(buttons[UP].uno, INPUT_PULLUP);
   buttons[ENTER].uno = 10;
   pinMode(buttons[ENTER].uno, INPUT_PULLUP);

   init_sysclock_2 ();
   puts("Finite State Machine: Four States");
// while(1) loop routine runs over and over again forever:
    while(1) {
        /* execution code goes here */
        // delay(50);
        printf("Entering FSM, state = %d\n", state);
        switch (state)
        {
             case 0:
             // Power on State
                puts("state0");
                state0();
                break;
             ;
             case 1:
             // Audible State
                puts("state1");
                state1();
                break;
             ;
             case 2:
             // Audible State
                puts("state2");
                state2();
                break;
             ;
             case 3:
             // Audible State
                puts("state3");
                state3();
                break;
             ;
             default:
               puts("Default found");
             //C Statements
             ;
        }
    }
    return(0);
}