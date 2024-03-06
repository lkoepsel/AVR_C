// K&R 2nd pgs 105-6, Character Pointers and Functions
// Use examples to demonstrate using char pointers in a function
// Demonstrate the value of using a max size test in copying strings
// showing cost of execution time to be minimal, ~1ms or 15 62.5ns clock cycles

#include <stdio.h>
#include <delay.h>
#include "uart.h"

// strcopy: copy t to s: array subscript version
void strcpy_1(char *s, char *t);

// strcopy: copy t to s: pointer version 1
// increment pointers separately
void strcpy_p1(char *s, char *t);

// strcopy: copy t to s: pointer version 2
// move pointer increment into comparison
void strcpy_p2(char *s, char *t);

// strcopy: copy t to s: pointer version 3
// comparison to \0 is redundent,
// as once t contains \0 the expression is false, i.e, (*s = \0)
void strcpy_p3(char *s, char *t); 

// strcopy: copy t to s: pointer version 3, with size check
// adds "max", a transfer limit, to stop buffer overflow issues
// On return: max = 0 char transferred is lessor of len(a) or len(b)
//            max > 0 char transferred is len(a) 
void strcpyn_p3(char *s, char *t, uint8_t *len);

// legal_string: prints entire string including last char which needs to be \0
void legal_string(char *s, uint8_t *l);

int main(void) 
{    
    init_serial();

    // set pin to output
    DDRB |= (_BV(PORTB5));

    char *a0 = "a0123a";
    char *b0 = "b01b";
    uint8_t max0 = 6;

    puts("\nK&R strcpyn_p3 Examples: max = len(a)");

    puts("*** a>b ***");
    printf("Before a: %s b: %s\n", a0, b0);
    uint8_t temp = max0;
    strcpyn_p3(a0, b0, &max0);
    uint8_t copied = temp;
    if (max0 > 0)
    {
        copied = temp - max0;
    }
    
    printf("After a: %s b: %s char copied: %u\n", a0, b0, copied);
    legal_string(a0, &copied);

    char *a1 = "a1234a";
    char *b1 = "b123456b";
    uint8_t max1 = 6;

    puts("*** a<b ***");
    printf("Before a: %s b: %s\n", a1, b1);
    temp = max1;
    strcpyn_p3(a1, b1, &max1);
    copied = temp;
    if (max1 >= 1)
    {
        copied = temp - (max0 + 1);
    }
    
    printf("After a: %s b: %s char copied: %u\n", a1, b1, copied);
    legal_string(a1, &temp);

    char *a2 = "a23a";
    char *b2 = "b23b";
    uint8_t max2 = 4;

    puts("*** a=b ***");
    printf("Before a: %s b: %s\n", a2, b2);
    temp = max2;
    strcpyn_p3(a2, b2, &max2);
    copied = temp;
    if (max2 >= 1)
    {
        copied = temp - (max2 + 1);
    }
    
    printf("After a: %s b: %s char copied: %u\n", a2, b2, copied);
    legal_string(a2, &temp);

    // Latency test - what is the cost in time for preventing buffer overflows
    // strcpy_p3 no check  =>  2.25us 
    // strcpyn_p3 size check  => 3.13us
    // Delta is ~880ns or 14 62.5 clock cycles
    for (;;)
    {
        char *a2 = "01234567890123456789012345678901234567890";
        char *b2 = "01234567890123456789012345678901234567890";
        // uint8_t max = 40;

        // strcpyn_p3(a2, b2, &max);
        strcpy_p3(a2, b2);

    }

    return 0;
}

void strcpy_1(char *s, char *t)
{
    int8_t i;

    i = 0;
    while((s[i] = t[i]) != '\0')
    {
        i++;
    }
}

void strcpy_p1(char *s, char *t) 
{

    while((*s = *t) != '\0')
    {
        s++;
        t++;
    }
}

void strcpy_p2(char *s, char *t) 
{

    while((*s++ = *t++) != '\0')
    {
        ;
    }
}

void strcpy_p3(char *s, char *t) 
{
    while((*s++ = *t++))
    {
        PINB |= (_BV(PORTB5));
    }
}

void strcpyn_p3(char *s, char *t, uint8_t *len) 
{
    while((*s++ = *t++) && (--(*len)))
    {
        PINB |= (_BV(PORTB5));
    }
}

void legal_string(char *s, uint8_t *l)
{
    uint8_t i = 0;
    printf("'");
    while (i < *l)
    {
        printf("%c", *s);
        s++;
        i++;
    }
    if (*s == '\0')
    {
        printf("' legal string ending in 0\n");
    }
}
