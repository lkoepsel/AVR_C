// pointers - explore using pointers

#include <stdio.h>
#include "uart.h"

int16_t addition(int16_t a, int16_t b) { return a + b; }
int16_t subtraction(int16_t a, int16_t b) { return a - b; }

int main(void) {    

    init_serial();
    
    // Simple Pointers
    int16_t x = 1234;
    int16_t y = 5678;
    int16_t *p_x;
    int16_t *p_y;
    int16_t *p_z;

    x++;
    y--;

    p_x = &x;
    p_y = &y;
    p_z = 0;

    // Pointers to pointers
    int16_t **p_p_x;
    p_p_x = &p_x;

    // Pointers and Arrays
    uint8_t numbers[] = {0, 1, 2, 3, 4};
    uint8_t *p_numbers;
    numbers[3] = 33;
    p_numbers = numbers;

    // Pointers and Structures
    struct LED
    {
       volatile uint8_t pin;    // Uno pin 
       uint8_t state;           // Is pin HIGH or LOW
       uint16_t on;             // Time on
       uint16_t off;            // Time off
       uint16_t elapsed;        // Time elapsed sinced last in loop
    } ;

    struct LED *p_LED;
    struct LED LED0;
    LED0.pin = 13;
    LED0.state = 1;
    LED0.on = 1000;
    LED0.off = 500;
    LED0.elapsed = 237;
    p_LED = &LED0;

    // Pointers and Functions
    int16_t (*p_func)(int16_t a, int16_t b);

    // Output
    puts("Simple Pointers");
    printf("The address of x (p_x) is %p and its value is %i (x)\n", p_x, x);        
    printf("The address of y (p_y) is %p and its value is %i (y)\n", p_y, y);
    if (!p_z) 
    {
        printf("The address of z is %p and it is 0\n", p_z);
    }
    
    puts("\nUnderstanding * and &");
    printf("The value of p_x is %p which is an address\n", p_x);
    printf("The value of *p_x is %i which is the value stored at %p\n",\
        *p_x, p_x);        
    printf("The value of &p_x is %p which ", &p_x);    
    printf("is the address which contains the address %p\n", p_x);    

    puts("\nPointers to pointers");
    printf("The address of the pointer to x is %p\n", p_p_x);
    printf("Addr: %p contains Addr: %p which contains: %i\n", p_p_x, p_x, x);        
    printf("      p_p_x   points to     p_x which contains     x\n");        
    
    puts("\nPointers and Arrays");
    printf("The address of numbers is %p, it contains %u == 0th value is %u\n",\
        p_numbers, *p_numbers, numbers[0]);
    for (uint8_t i = 0; i< sizeof(numbers)/sizeof(numbers[0]); i++)
    {        
        printf("Address %u of numbers is %p and %p and the values are %u and %u\n",\
            i, p_numbers, &numbers[i], *p_numbers, numbers[i]);
        p_numbers++;    
    }
    p_numbers = numbers;
    printf("The value of *(p_numbers + 3) is %u\n", *(p_numbers + 3));
    
    puts("\nPointers and Structures");
    printf("LED0 %p contains pin %u state %u on %u off %u and elapsed %u\n",\
            p_LED, (*p_LED).pin, (*p_LED).state, p_LED->on, p_LED->off, \
            p_LED->elapsed);

    puts("\nPointers and Functions");
    p_func = addition;
    int16_t results = (*p_func)(x, y);
    printf("p_func points to addition at address %p with %i + %i = %i\n",\
        p_func, x, y, results);
    p_func = subtraction;
    results = (*p_func)(x, y);
    printf("p_func points to subtraction at address %p with %i - %i = %i\n",\
        p_func, x, y, results);
    printf("End of Output\n");
    return 0;
}
