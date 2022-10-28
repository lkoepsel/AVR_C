// servo_0: Demo how to control two servos using Timer/Counter 0

// Circuit setup:
// 1. The servo has four leads, power(red), ground(brown), control(orange)
// to pin 6 and position pot feedback(white) to A0
// 2. The control pot has three leads, right(power), left(ground) and 
// center to A2
// 3. The Uno power(5V) and ground(GND) are connected to power and 
// ground rails on the breadboard

// Overview:
// Setup servo clock to 60.96kHz signal, variable pulse width pins 6(A) and 5(B)
// Read control pot and use map() to go from 10bit ADC value to 8bit OCR0n value
// Set OCR0n with new value and get new position of servo

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

// Example parameters                             
// Frequency: 16MHz / 256 / 1024 = 61.35Hz(calc) or 60.96Hz(measured)                  
// Pin 5/PD5/OCR0B=15 has a 5.8% duty cycle or 15/255 => 1.025ms (measured)                    
// Pin 6/PD6/OCR0A=30 has a 11.6% duty cycle or 30/255 => 1.987ms (measured)
#include <avr/io.h>
#include "pinMode.h"
#include "delay.h"
#include "analogRead.h"
#include "sysclock.h"
#include "map.h"
#include "unolib.h"

// Parameters for Adafruit 1449 Microservo with feedback
// Two can be controlled, code only controls one at this time
const uint8_t PULSE_MIN = 6;            // min width pulse (.5ms)
const uint8_t PULSE_MAX = 36;           // max width pulse (2.3ms)
const uint16_t SERVO_DELAY = 250;       // allow servo to move 
const uint8_t SERVO_CONTROL_0 = 6;      // servo 0 control pin
const uint8_t SERVO_POS_PIN_0 = A0;     // servo 0 position pin (pot feedback)
const uint8_t SERVO_CONTROL_1 = 5;      // servo 1 control pin
const uint8_t SERVO_POS_PIN_1 = A1;     // servo 0 position pin (pot feedback)
const uint8_t POT_PIN = A2;             // external pot to control servo pos
const uint16_t POT_MAX = 1023;          // max value for control pot
const uint16_t POT_MIN = 0;             // min value for control pot

// In rare situations, variables have been optimized out (determined by gdb)
// Made volatile to ensure they don't
volatile uint16_t control_pos = POT_MIN;
volatile uint16_t servo_pos = 0;
volatile uint8_t servo_pulse = PULSE_MIN;

void init_servo_clock(void)
{
    pinMode(SERVO_CONTROL_0, OUTPUT);
    pinMode(SERVO_CONTROL_1, OUTPUT);
    pinMode(SERVO_POS_PIN_0, INPUT);
    pinMode(SERVO_POS_PIN_1, INPUT);
    pinMode(POT_PIN, INPUT);

    // reset Timer 0 control registers to ensure clean slate for new timer
    TCCR0A = 0;
    TCCR0B = 0; 

    // Generate a 60.96kHz pulse on 6 and 5 using Fast PWM
    // OCR0A/B control width of pulse on 6 and 5
    // TCCR0A [ COM0A1 COM0A0 COM0B1 COM0B0 0 0 WGM01 WGM00 ] = 0b1010 0011
    TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
    // TCCR0B [ FOC2A FOC2B 0 0 WGM02 CS02 CS01 CS00 ] = 0b0000 0101
    TCCR0B =  _BV(CS02) | _BV(CS00);
    OCR0A = PULSE_MIN;              // start with servo 0 at 0 degrees
    OCR0B = PULSE_MAX;              // start with servo 1 at 180 degrees
}

// controls servo 0 angle, duplicate to control servo 1
// delay to ensure servo has completed move, before reading position
uint16_t set_servo_pos_0(uint8_t angle_value)
{
   uint8_t angle = constrain8_t(angle_value, PULSE_MIN, PULSE_MAX);
   OCR0A = angle;
   delay(SERVO_DELAY);
   return analogRead(SERVO_POS_PIN_0);
}

int main (void)
{   
    init_servo_clock();

    // get control pot value and convert to pulse width using map()
    // set servo position, function returns new position
    // delay(1) exists as a debugger aid, ensures a line to BP to check values
    while(TRUE)
    {
        control_pos = analogRead(POT_PIN);
        servo_pulse = map(control_pos, POT_MIN, POT_MAX, PULSE_MIN, PULSE_MAX);
        servo_pos = set_servo_pos_0(servo_pulse );
        delay(1);
    }
    return 0;
}
