/* One line kernal for multitasking
*  https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/
*  Tasks are individually setup using a struct
*  Fundamental premise is an on/off signal, whether LED, or speaker
*/

#include <avr/io.h>
#include <stdio.h>
#include "delay.h"
#include "pinMode.h"
#include "sysclock.h"
#include "digitalWrite.h"
#include "uart.h"
#include "analogRead.h"
#include "serialRead.h"

/* Defaults:
*  NTASKS: Number of tasks to be defined
*  DEFAULT_ON/DEFAULT_OFF: Times (msec) for task to be on/off
*  With On/Off set to 435, three tasks run at 18kHz (fastest freq)
*/
#define NTASKS 1

// FREQ/MIN/MAX change per CLKIO prescalar, current values 55/127/520 use CS00
const uint16_t FREQ_60Hz = 520; //  count to create a ~60Hz pulse (59.98Hz)
const uint8_t MIN_PULSE = 55;   // count to create ~.888ms or 0 degrees servo
const uint8_t MAX_PULSE = 127;  // count to create ~2.4ms or 180 degrees servo

const uint8_t SERVO_CONTROL = 12;
const uint8_t SERVO_POS_PIN = A0;
const uint16_t SERVO_DELAY = 250;

uint16_t on_0;
uint16_t off_0;
uint16_t on_1;
uint16_t off_1;
uint16_t on_2;
uint16_t off_2;


typedef struct task {
   volatile uint8_t pin;    // Uno pin 
   uint8_t state;           // Is pin HIGH or LOW
   uint16_t on;             // Time on
   uint16_t off;            // Time off
   uint16_t elapsed;        // Time elapsed sinced last in loop
   uint16_t new_on;            // New Time for on loop, if 0, don't update
   uint16_t new_off;            // New Time for off loop
} task;

task tasks[NTASKS];

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

void init_servo_clock (void)          
{
    // Timer 0 Configuration, 8bit Fast PWM p113-7
    // TCCR0A - Timer/Counter0 Control Register                 
    // [ COM0A1 COM0A0 COM0B1 COM0B0 0 0 WGM01 WGM00 ]          

    // TCCR0B - Timer/Counter0 Control Register                 
    // [ FOC0A FOC0B 0 0 WGM02 CS02 CS01 CS20 ]                 
    TCCR0A |= 0;
    TCCR0B |= _BV(CS00);
    TIMSK0 |= _BV(TOIE0);
    sei();
}

void init(uint8_t index, uint8_t pin, uint8_t state, uint16_t on, uint16_t off,\
    uint16_t elapsed, uint16_t new_on, uint16_t new_off)
{
    tasks[index].pin = pin;
    tasks[index].state = state;
    tasks[index].on = on;
    tasks[index].off = off;
    tasks[index].elapsed = elapsed;
    tasks[index].new_on = new_on;
    tasks[index].new_off = new_off;
    pinMode(pin, OUTPUT);
}

void update (uint8_t taskID) 
{
    uint16_t now = servo_clock();
    if((tasks[taskID].state == HIGH) &&\
        (now - tasks[taskID].elapsed >= tasks[taskID].on))
    {
        tasks[taskID].state = LOW;  // Turn it off
        tasks[taskID].elapsed = now;  // Remember the time
        digitalWrite(tasks[taskID].pin, LOW);
    }
    else if (tasks[taskID].state == LOW) 
    {
        if (now - tasks[taskID].elapsed >= tasks[taskID].off)
        {
            tasks[taskID].state = HIGH;  // turn it on
            tasks[taskID].elapsed = now;   // Remember the time
            digitalWrite(tasks[taskID].pin, HIGH);
    
        }
        else
        {
            if  ((tasks[taskID].new_on != 0))
            {
                tasks[taskID].on = tasks[taskID].new_on;
                tasks[taskID].new_on = 0;
            }
        }
    }
    return;
} 

uint16_t set_pwm_0(uint8_t angle_value)
{
   uint8_t angle = constrain(angle_value, MIN_PULSE, MAX_PULSE);
   OCR0A = angle;
   delay(SERVO_DELAY);
   return analogRead(SERVO_POS_PIN);
}

void ramp_angle(void)
{
    for (uint8_t pulse = MIN_PULSE; pulse <= MAX_PULSE; pulse++)
    {
        on_0 = pulse;
        off_0 = FREQ_60Hz + (FREQ_60Hz - on_0);
        uint8_t update = 1;
        while(update)
        {
            if (tasks[0].state == HIGH)
            {
                tasks[0].new_on = pulse;
                tasks[0].new_off = FREQ_60Hz + (FREQ_60Hz - pulse);
                update = 0;
            }
        }
    }
}

int main(void)
{
    init_servo_clock ();
    init_serial();

    // init tasks: {index, pin, state, on, off, elapsed}
    on_0 = MIN_PULSE;
    off_0 = FREQ_60Hz + (FREQ_60Hz - on_0);
    on_1 = MIN_PULSE;
    off_1 = FREQ_60Hz + (FREQ_60Hz - on_1);
    on_2 = MIN_PULSE;
    off_2 = FREQ_60Hz + (FREQ_60Hz - on_2);

    init(0, 4, LOW, on_0, off_0, 0, 0, 0);
    init(1, 5, LOW, on_1, off_1, 0, 0, 0);
    init(2, 6, LOW, on_2, off_2, 0, 0, 0);
    // init(3, 7, LOW, on_2, off_2, 0);
    // init(4, 8, LOW, on_2, off_2, 0);
    // init(5, 9, LOW, on_2, off_2, 0);
    // init(6, 10, LOW, on_2, off_2, 0);
    // init(7, 11, LOW, on_2, off_2, 0);
    // init(8, 12, LOW, on_2, off_2, 0);

    pinMode(8, OUTPUT);
    uint16_t test_elapsed = 0;
    uint16_t test_interval = FREQ_60Hz * 30;
    uint16_t test_pulse = MIN_PULSE;
    while (1)
    {
    for (uint8_t task_cntr=0; task_cntr < NTASKS; ++task_cntr)
        {
            update(task_cntr);
        }
        uint16_t test_now = servo_clock();
        if ((test_now - test_elapsed) >= test_interval)
        {
            tog_bit(PINB, 0);
            if (tasks[0].on == HIGH)
            {
                tasks[0].new_on = MIN_PULSE;
                tasks[0].new_off = FREQ_60Hz + (FREQ_60Hz - tasks[0].new_on);
                test_elapsed = test_now;
                test_pulse++;
            }
        }
        }
    return 0; 
}
