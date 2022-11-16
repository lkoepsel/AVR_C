#include "frequency.h"

void blue_led_on() {

    // Blue LED Indicator, ON
    // set UNO pin 2/PD2 to output, 976.6Hz, duty cycle based on parameter
    pinMode(BLUE_LED, OUTPUT);

return;
}   

void blue_led_off() {

    // Blue LED Indicator, OFF
    // set UNO pin 6/PD6 to input to turn off LED
    pinMode(BLUE_LED, INPUT);
    
return;
}   

void blue_led(uint8_t intensity) {

    // Blue LED Indicator, Dim
    // set UNO pin 6/PD6 to output, 976.6Hz, 12% duty cycle
    blue_led_on();
    analogWrite(BLUE_LED, intensity);
    
return;
}   
