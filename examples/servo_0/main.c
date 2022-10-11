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
#include <stdio.h>
#include "uart.h"
#include "pinMode.h"
#include "delay.h"
#include "serialRead.h"
#include "analogRead.h"
#include "sysclock.h"

const uint8_t MIN_PULSE = 6;
const uint8_t MAX_PULSE = 35;
const uint8_t SERVO_CONTROL = 12;
const uint8_t SERVO_POS_PIN = A0;
const uint16_t SERVO_DELAY = 250;

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

void init_pwm_0(uint8_t pin)
{
    pinMode(SERVO_POS_PIN, INPUT);

    // reset both timer/counters
    TCCR0A = 0;
    TCCR0B = 0; 

    // set UNO pin 5/PD5 and pin 6/PD6 to output
    DDRD |= _BV(DDD6) | _BV(DDD5);
    
    // TCCR0A [ COM0A1 COM0A0 COM0B1 COM0B0 0 0 WGM01 WGM00 ] = 0b10100011
    TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
    // TCCR0B [ FOC2A FOC2B 0 0 WGM02 CS02 CS01 CS00 ] = 0b00000101
    TCCR0B =  _BV(CS02) | _BV(CS00);
    OCR0A = MIN_PULSE;
    OCR0B = MIN_PULSE;
}

uint16_t set_pwm_0(uint8_t angle_value)
{
   uint8_t angle = constrain(angle_value, MIN_PULSE, MAX_PULSE);
   OCR0A = angle;
   delay(SERVO_DELAY);
   return analogRead(SERVO_POS_PIN);
}

void set_angle(void)
{
    uint8_t angle_value = serialRead();
    uint8_t pulse = (angle_value / 6) + 6;
    uint16_t position = set_pwm_0(pulse);
    printf("For requested angle %u, pulse assigned %u and servo position: %u\n",\
        angle_value, pulse, position);
}

void ramp_angle(void)
{
    for (uint8_t pulse = MIN_PULSE; pulse <= MAX_PULSE; pulse++)
    {
        uint16_t position = set_pwm_0(pulse);
        uint8_t angle = (pulse - 6) * 6;
        printf("For pulse %u, angle is %u, servo position: %u\n",\
            pulse, angle, position);

    }
}
int main (void)
{   
    init_pwm_0(SERVO_CONTROL);
    init_serial();

    puts("Servo Calibration");
    ramp_angle();
    puts("Enter Desired Angle (0-180)");
    while(TRUE)
    {
        set_angle();
    }
    return 0;
}
