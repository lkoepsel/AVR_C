#include "main.h"
#include "uart.h"

/* Put your global variables here */
// state contains the current state of the FSM

const uint8_t BIT_0 = 4;
const uint8_t BIT_1 = 5;
const uint8_t BLUE_LED = 6;

uint8_t state = 0;

/* Main */ 
int main() {

   init_serial();
   pinMode(BIT_0, OUTPUT);
   pinMode(BIT_1, OUTPUT);

   buttons[UP].uno = 2;
   pinMode(buttons[UP].uno, INPUT_PULLUP);
   buttons[ENTER].uno = 3;
   pinMode(buttons[ENTER].uno, INPUT_PULLUP);

   init_sysclock_2 ();
   // Use init_RESET() if you want to setup a soft reset using a user defined
   // button as on the ATmega328PB Xplained Mini
   // init_RESET();
   puts("Finite State Machine: Four States (0-3)");

    while(1) {
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
             // State 1
                puts("state1");
                state1();
                break;
             ;
             case 2:
             // State 2
                puts("state2");
                state2();
                break;
             ;
             case 3:
             // State 3
                puts("state3");
                state3();
                break;
             ;
             default:
               puts("Default found");
             ;
        }
    }
    return 0;
}
