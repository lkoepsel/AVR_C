// servo_0: Demo servo control using Timer/Counter 0                        

// Timer 0 Configuration, 8bit Fast PWM p113-7
// TCCR0A - Timer/Counter0 Control Register                 
// [ COM0A1 COM0A0 COM0B1 COM0B0 0 0 WGM01 WGM00 ]          

// TCCR0B - Timer/Counter0 Control Register                 
// [ FOC0A FOC0B 0 0 WGM02 CS02 CS01 CS20 ]                 

// COM0A1:0 = 10 => Clear OC0A on compare match (non-inverting)             
// COM0B1:0 = 10 => Clear OC0B on compare match (non-inverting)
// WGM02:0 = 011 => Fast PWM, Update at Bottom, TOV=MAX   
// CS02:0 = 101 => clkio / (256 * 1024), 101 => 1/1024                          

// PWM Pins p97   
// ARD5 PD5 OC2B 8bit Timer/Counter 0 OCR0B setup but not implemented                       
// ARD6 PD6 OC2A 8bit Timer/Counter 0 OCR0A controls servo 0

// Specific to parameters below                             
// Frequency: 16MHz / 256 / 1024 = 61.35Hz(calc) or 60.96Hz(measured)                  
// Pin 5/PD5/OCR0B has a 5.8% duty cycle or 15/255 => 1.025ms (measured)                    
// Pin 6/PD6/OCR0A has a 11.6% duty cycle or 30/255 => 1.987ms (measured)
#include <avr/io.h>
#include "pinMode.h"
#include "delay.h"
#include "analogRead.h"
#include "sysclock.h"
#include "map.h"

const uint8_t PULSE_MIN = 6;
const uint8_t PULSE_MAX = 36;
const uint16_t SERVO_DELAY = 250;
const uint8_t SERVO_CONTROL_0 = 6;
const uint8_t SERVO_POS_PIN_0 = A0;
const uint8_t SERVO_CONTROL_1 = 5;
const uint8_t SERVO_POS_PIN_1 = A1;
const uint8_t POT_PIN = A2;
const uint16_t POT_MAX = 1023;
const uint16_t POT_MIN = 0;
volatile uint16_t pot_value = POT_MIN;
volatile uint16_t servo_pos = 0;


uint8_t PULSE = PULSE_MIN;

uint8_t constrain(uint8_t value, uint8_t min, uint8_t max) {
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }
    else
    {
        return value;
    }
}

void init_pwms(void)
{
    pinMode(SERVO_CONTROL_0, OUTPUT);
    pinMode(SERVO_CONTROL_1, OUTPUT);
    pinMode(SERVO_POS_PIN_0, INPUT);
    pinMode(SERVO_POS_PIN_1, INPUT);
    pinMode(POT_PIN, INPUT);

    // reset both timer/counters
    TCCR0A = 0;
    TCCR0B = 0; 

    // Generate a 60.96kHz pulse on 6 and 5 using Fast PWM
    // OCR0A/B control width of pulse on 6 and 5
    // TCCR0A [ COM0A1 COM0A0 COM0B1 COM0B0 0 0 WGM01 WGM00 ] = 0b10100011
    TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
    // TCCR0B [ FOC2A FOC2B 0 0 WGM02 CS02 CS01 CS00 ] = 0b00000101
    TCCR0B =  _BV(CS02) | _BV(CS00);
    // OCR0A = PULSE_MIN;
    OCR0B = PULSE_MAX;
}

uint16_t set_pwm_0(uint8_t angle_value)
{
   uint8_t angle = constrain(angle_value, PULSE_MIN, PULSE_MAX);
   OCR0A = angle;
   delay(SERVO_DELAY);
   return analogRead(SERVO_POS_PIN_0);
}

int main (void)
{   
    init_pwms();

    while(TRUE)
    {
        pot_value = analogRead(POT_PIN);
        PULSE = map(pot_value, POT_MIN, POT_MAX, PULSE_MIN, PULSE_MAX);
        servo_pos = set_pwm_0(PULSE);
        delay(1);
    }
    return 0;
}
