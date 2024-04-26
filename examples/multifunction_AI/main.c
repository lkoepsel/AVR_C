// Multi-function AI - asked CHATGPT for a multi-tasking program
// Writing a multi-tasking framework for an ATmega328P microcontroller using 
// avr-gcc involves implementing a cooperative multitasking system. 
// Here's a simplified example with a priority scheme for up to MAX_TASKS tasks. 
// Note that this is a basic framework and might require further customization 
// to suit your specific application.

// The ISR and Interrupt setup were changed to match the existing sysclock.
#include "sysclock.h"
#include "pinMode.h"

void task1();
void task2();
void task3();

uint8_t LED1 = LED_BUILTIN;
uint8_t LED2 = 4;
uint8_t LED3 = 5;
uint8_t LEDM = 6;

#define MAX_TASKS 3

// Array to hold the task control blocks
Task tasks[MAX_TASKS];

// Add a task to the multitasking framework
void multitask_add_task(TaskFunction function, uint16_t period_ticks, uint8_t priority) 
{
    for (int i = 0; i < MAX_TASKS; i++) {
        if (tasks[i].function == NULL) {
            tasks[i].function = function;
            tasks[i].previous_ticks = period_ticks;
            tasks[i].period_ticks = period_ticks;
            tasks[i].priority = priority;
            return;
        }
    }
}

// Compare function for qsort to sort tasks by priority
int compare_tasks(const void* a, const void* b) {
    const Task* taskA = (const Task*)a;
    const Task* taskB = (const Task*)b;
    return taskA->priority - taskB->priority;
}

// Main loop for multitasking
int main() {
    init_sysclock_1();

    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LEDM, OUTPUT);

    // Add your tasks here
    multitask_add_task(task1, 100, TASK_PRIORITY_HIGH);
    multitask_add_task(task2, 200, TASK_PRIORITY_MEDIUM);
    multitask_add_task(task3, 300, TASK_PRIORITY_LOW);


    while (1) {
        // Sort tasks by priority
        qsort(tasks, MAX_TASKS, sizeof(Task), compare_tasks);

        // Task scheduling and execution
        for (int i = 0; i < MAX_TASKS; i++) {
            if (ticks() - tasks[i].previous_ticks > tasks[i].period_ticks) 
            {
                tasks[i].function();
            }
            tasks[i].previous_ticks = ticks();
        }
    }

    return 0;
}

// Example tasks
void task1() {
    digitalWrite(LED1, TOG);
}

void task2() {
    digitalWrite(LED2, TOG);
}

void task3() {
    digitalWrite(LED3, TOG);
}
