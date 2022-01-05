#include "sysclock.h"
#include "unolib.h"
#include "button.h"

volatile uint16_t sys_ctr = 0;

extern button buttons[max_buttons];

/* ISR for system counter and button presses 
* 15ms of the delay is due to the button press checking in the ISR
* if button presses aren't required, comment out the code
*/
ISR (TIMER2_COMPA_vect)      
{
    /* button press check: make SCALAR1 SCALAR01_64 in sysclock.h   */
    //  and uncomment code below                                     
    for (int i = 0; i < max_buttons; i++) {
        buttons[i].pressed = is_button_pressed(i);
    }

    sys_ctr++;
}

uint16_t millis() {

      return(sys_ctr);
}

void init_sysclock (void)          
{
    /* Initialize timer 2
    * TCCR2A [ COM2A1 COM2A0 COM2B1 COM2B0 0 0 WGM21 WGM20 ] = 00000001
    * WGM22 WGM20 => PWM, Phase Correct, TOP = OCRA
    * TCCR2B [ FOC2A FOC2B 0 0 WGM22 CS22 CS21 CS20 ]
    * CS22 CS20 => scalar of 32
    * Frequency = 16 x 10^6 / 8 / 40 = 50kHz
    * -1 to account for overhead = 39
    * Counter performs another divide by 2 => 25kHz
    * Test using example/millis (delay(1000) = 40527 ticks)
    */
    TCCR2A |= (_BV(WGM20));
    TCCR2B |= ( _BV(WGM22) | _BV(CS21) ) ;
    OCR2A = 39;
    TIMSK2 |= _BV(OCIE2A);

    sei ();
}
