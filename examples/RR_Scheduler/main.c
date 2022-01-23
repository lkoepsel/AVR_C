/**
AVR Round Robbin Scheduler
Hardware: ATMega8 running at 8MHz
https://sites.google.com/site/avrtutorials2/scheduler
Updated 12/6/21 for ATmega328P(Uno)

This is an example only as the ISR TIMER0_OVF_vect conflicts with tone()
If you wish to test this code, comment out the ISR TIMER0_OVF_vect in tone.c
*/

#include<avr/interrupt.h>
#include<inttypes.h>

#include "pinMode.h"
#include "unolib.h"

#define MAX_TASKS (10)

// task states
#define RUNNABLE (0x00)
#define RUNNING  (0x01)
#define STOPPED  (0x02)
#define ERROR    (0x03)


// a task "type"
// pointer to a void function with no arguments
typedef void (*task_t)(void);

// basic task control block (TCB)
typedef struct __tcb_t
{
    uint8_t id; // task ID
    task_t task; // pointer to the task
    // delay before execution
    uint16_t delay, period; 
    uint8_t status; // status of task
} tcb_t;


// scheduler functions
void initScheduler(void);
void addTask(uint8_t, task_t, uint16_t);
void deleteTask(uint8_t);
uint8_t getTaskStatus(uint8_t);
void dispatchTasks(void);

// prototypes of tasks
void Task1(void);
void Task2(void);

// the task list
tcb_t task_list[MAX_TASKS];

// keeps track of number of timer interrupts
uint16_t count = 0;

// scheduler function definitions

// initialises the task list
void initScheduler(void)
{
    for(uint8_t i=0; i<MAX_TASKS; i++)
    {
        task_list[i].id = 0;
        task_list[i].task = (task_t)0x00;
        task_list[i].delay = 0;
        task_list[i].period = 0;
        task_list[i].status = STOPPED;
    }
}

// adds a new task to the task list
// scans through the list and
// places the new task data where
// it finds free space
void addTask(uint8_t id, task_t task, 
             uint16_t period)
{
    uint8_t idx = 0, done = 0x00;    
    while( idx < MAX_TASKS )
    {
        if( task_list[idx].status == STOPPED )
        {
            task_list[idx].id = id;
            task_list[idx].task = task;
            task_list[idx].delay = period;
            task_list[idx].period = period;
            task_list[idx].status = RUNNABLE;            
            done = 0x01;
        }
        if( done ) break;
        idx++;
    }

}

// remove task from task list
// note STOPPED is equivalent
// to removing a task
void deleteTask(uint8_t id)
{    
    for(uint8_t i=0;i<MAX_TASKS;i++)
    {
        if( task_list[i].id == id )
        {
            task_list[i].status = STOPPED;
            break;
        }
    }
}

// gets the task status
// returns ERROR if id is invalid
uint8_t getTaskStatus(uint8_t id)
{
    for(uint8_t i=0;i<MAX_TASKS;i++)
    {
        if( task_list[i].id == id )
            return task_list[i].status;
    }
    return ERROR;
}

// dispatches tasks when they are ready to run
void dispatchTasks(void)
{
    for(uint8_t i=0;i<MAX_TASKS;i++)
    {
        // check for a valid task ready to run
        if( !task_list[i].delay && 
             task_list[i].status == RUNNABLE )
        {
            // task is now running
            task_list[i].status = RUNNING;            
            // call the task
            (*task_list[i].task)(); 

            // reset the delay
            task_list[i].delay = 
                task_list[i].period; 
            // task is runnable again
            task_list[i].status = RUNNABLE;
        }
    }    
}    

// generates a "tick"
// each tick 16x10^6/256/8 => 7812us apart
ISR(TIMER0_OVF_vect)
{
    count ++;
    if( count == 10 ) 
    {
        count = 0;

        // cycle through available tasks
        for(uint8_t i=0;i<MAX_TASKS;i++)
        {                
            if( task_list[i].status == RUNNABLE )
                task_list[i].delay--;
        }
    }
}

// Task definitions

void Task1(void)
{
    static uint8_t status = 0x01;
    if( status )
        PORTD |= _BV(PD2);
    else
        PORTD &= ~_BV(PD2);
    status = !status;
}


void Task2(void)
{
    static uint8_t status = 0x01;
    if( status )
        PORTD |= _BV(PD3);
    else
        PORTD &= ~_BV(PD3);
    status = !status;
}

void Task3(void)
{
    static uint8_t status = 0x01;
    if( status )
        PORTD |= _BV(PD4);
    else
        PORTD &= ~_BV(PD4);
    status = !status;
}

int main(void)
{
    // Setup T/C0 as the multi-tasking clock 
    TCCR0A = _BV(WGM00); 
    TCCR0B = _BV(CS01); 
    TIMSK0 = _BV(TOIE0); 
    // set PORTD bit3, 5 and 6 as outputs
    DDRD = _BV(PD2)| _BV(PD3) | _BV(PD4);  

    // set up the task list
    initScheduler();

    // add tasks, id is arbitrary
    // a period of 25 = 1Hz
    // task1 runs every 1/2 second
    addTask(1, Task1, 10);

    // task2 runs every 1 second
    addTask(2, Task2, 10);    

    // task3 runs every 2 seconds
    addTask(3, Task3, 10);    

    // enable all interrupts
    sei();    
    for(;;)
        dispatchTasks();
    return 0; // will never reach here
}
