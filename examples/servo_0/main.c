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
const uint8_t MAX_PULSE = 36;
const uint8_t SERVO_CONTROL_0 = 6;
const uint8_t SERVO_POS_PIN_0 = A0;
const uint8_t SERVO_CONTROL_1 = 5;
const uint8_t SERVO_POS_PIN = A1;
const uint16_t SERVO_DELAY = 250;

// struct servo {
//    uint8_t ctrl_pin;  // Uno TC0 pin (6 or 5) to control the servo
//    uint8_t pos_pin;            // Uno analog pin to read position
//    uint16_t pulse;             // pulse value to move to position
//    uint16_t position;          // position of servo
//    uint8_t *OCR0n;             // Address of the timer register for the pulse
// } servo;

// struct servo servos[2]; // as servo pwm is limited to TC0, only 2 servos allowed

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

// void init_servo(uint8_t index, uint8_t ctrl_pin, uint8_t pos_pin,
//     uint16_t pulse, uint16_t position, uint8_t *OCR0n)
// {
//     servo[index].ctrl_pin = ctrl_pin;
//     servo[index].pos_pin = pos_pin;
//     servo[index].pulse = pulse;
//     servo[index].position = position;
//     servo[index].OCR0n = OCR0n;
// }

void init_pwm(void)
{
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(SERVO_POS_PIN, INPUT);

    // reset both timer/counters
    TCCR0A = 0;
    TCCR0B = 0; 

    // TCCR0A [ COM0A1 COM0A0 COM0B1 COM0B0 0 0 WGM01 WGM00 ] = 0b10100011
    TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
    // TCCR0B [ FOC2A FOC2B 0 0 WGM02 CS02 CS01 CS00 ] = 0b00000101
    TCCR0B =  _BV(CS02) | _BV(CS00);
    OCR0A = MIN_PULSE;
    OCR0B = MIN_PULSE;
}

uint16_t set_pwm(uint8_t angle_value)
{
   uint8_t angle = constrain(angle_value, MIN_PULSE, MAX_PULSE);
   OCR0A = angle;
   delay(2000);
   return analogRead(SERVO_POS_PIN);
}

void serial_angle(void)
{
    uint8_t angle_value = serialRead();
    uint8_t pulse = (angle_value / 6) + 6;
    uint16_t position = set_pwm(pulse);
    printf("For requested angle %u, pulse assigned %u and servo position: %u\n",\
        angle_value, pulse, position);
}

void ramp_angle(void)
{
    for (uint8_t pulse = MIN_PULSE; pulse <= MAX_PULSE; pulse++)
    {
        uint16_t position = set_pwm(pulse);
        uint8_t angle = (pulse - 6) * 6;
        printf("For pulse %u, angle is %u, servo position: %u\n",\
            pulse, angle, position);

    }
}
int main (void)
{   
    init_pwm();
    init_serial();

    puts("Servo Calibration");
    ramp_angle();
    // puts("Enter Desired Angle (0-180)");
    // while(TRUE)
    // {
    //     // serial_angle();
    //     uint16_t position = set_pwm(MIN_PULSE);
    //     printf("Pulse assigned %u and servo position: %u\n",
    //         MIN_PULSE, position);
    //     delay(1000);
    //     position = set_pwm(MAX_PULSE);
    //     printf("Pulse assigned %u and servo position: %u\n",
    //         MAX_PULSE, position);
    //     delay(1000);
    // }
    return 0;
}
