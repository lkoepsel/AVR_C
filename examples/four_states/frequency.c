#include "frequency.h"

void blue_led_on() {

    // Blue LED Indicator, ON
    // set UNO pin 2/PD2 to output, 976.6Hz, duty cycle based on parameter
    // DDRD |=  _BV(BLUE_LED);
    pinMode(BLUE_LED, OUTPUT);

return;
}   

void blue_led_off() {

    // Blue LED Indicator, OFF
    // set UNO pin 6/PD6 to input to turn off LED
    // DDRD &=  ~(_BV(BLUE_LED));
    pinMode(BLUE_LED, INPUT);
    
return;
}   

void blue_led(uint8_t intensity) {

    // Blue LED Indicator, Dim
    // set UNO pin 6/PD6 to output, 976.6Hz, 12% duty cycle
    blue_led_on();
    analogWrite(BLUE_LED, intensity);
    
    // // TCCR0A [ COM0A1 COM0A0 COM0B1 COM0B0 0 0 WGM21 WGM20 ] = 11000010
    // TCCR0A |= (_BV(COM0A1) | _BV(WGM21) | _BV(WGM20));

    // // TCCR0B [ FOC2A FOC2B 0 0 WGM22 CS22 CS21 CS20 ]
    // TCCR0B |=  (_BV(CS21) | _BV(CS20));

    // OCR0A = intensity;
return;
}   
