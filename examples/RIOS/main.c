#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include "digitalWrite.h"
#include "unolib.h"
#include "pinMode.h"
#include "delay.h"
#include "uart.h"



typedef struct task {
   uint8_t running;                 // 1 indicates task is running
   uint8_t state;                   // State of state machine
   uint16_t period;                 // Rate at which the task should tick
   uint16_t elapsedTime;            // Time since task's previous tick
   uint16_t (*TickFct)(uint8_t);    // Function to call for task's tick
} task;

task tasks[3];

/* LEDs to indicate which task is running */
uint8_t LED1 = 2;               
uint8_t LED2 = 3;
uint8_t LED3 = 4;

const uint8_t tasksNum = 3;
const uint16_t tasksPeriodGCD = 5;
const uint16_t period1 = 5;
const uint16_t period2 = 10;
const uint16_t period3 = 20;

uint16_t TickFct_1(uint8_t state);
uint16_t TickFct_2(uint8_t state);
uint16_t TickFct_3(uint8_t state); 

uint8_t runningTasks[4] = {255};    // Track running tasks, [0] always idleTask
const uint16_t idleTask = 255;      // 0 highest priority, 255 lowest
uint8_t currentTask = 0;            // Index of highest priority task in runningTasks

unsigned schedule_time = 0;
ISR(TIMER2_OVF_vect) {
   uint8_t i;
   for (i=0; i < tasksNum; ++i) {   // Heart of scheduler code
      if (  (tasks[i].elapsedTime >= tasks[i].period) // Task ready
          && (runningTasks[currentTask] > i) // Task priority > current task priority
          && (!tasks[i].running) // Task not already running (no self-preemption)
         ) { 
        cli();
        tasks[i].elapsedTime = 0; // Reset time since last tick
        tasks[i].running = 1; // Mark as running
        currentTask += 1;
        runningTasks[currentTask] = i; // Add to runningTasks
        sei();

        tasks[i].state = tasks[i].TickFct(tasks[i].state); // Execute tick

        cli();
        tasks[i].running = 0; // Mark as not running
        runningTasks[currentTask] = idleTask; // Remove from runningTasks
        currentTask -= 1;
        sei();
      }
      tasks[i].elapsedTime += tasksPeriodGCD;
   }
}

void init_processor() {
    
    /*Set up timer 16 x 10^ 6 / 8 / 510 = 3.92kHz or an OVF every 255usecs */
    TCCR2A |= _BV(WGM20); // Phase Correct, PWM mode, 0xff is the default count
    TCCR2B |= _BV(CS21); // Prescaler=8
    TIMSK2 = _BV(TOIE2); //enables Timer/Counter0 Overflow Interrupt Enable
        
    /*Enable global interrupts*/
    sei();
}

int main(void)
{
    init_processor();
    init_serial();

    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);


   // Priority assigned to lower position tasks in array
   uint8_t i = 0;
   tasks[i].state = -1;
   tasks[i].period = period1;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].running = 0;
   tasks[i].TickFct = &TickFct_1;
   ++i;
   tasks[i].state = -1;
   tasks[i].period = period2;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].running = 0;
   tasks[i].TickFct = &TickFct_2;
   ++i;
   tasks[i].state = -1;
   tasks[i].period = period3;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].running = 0;
   tasks[i].TickFct = &TickFct_3;
    
    while(1)
    {
    }
}

uint16_t TickFct_1(uint8_t state) {
    digitalWrite(LED1, TOG);
    // puts("Task 1");
    return 0;
}

uint16_t TickFct_2(uint8_t state) {
    digitalWrite(LED2, TOG);
    // puts("Task 2");
    return 0;
}

uint16_t TickFct_3(uint8_t state) {
    digitalWrite(LED3, TOG);
    // puts("Task 3");
    return 0;
}
