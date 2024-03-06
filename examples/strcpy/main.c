// K&R 2nd pgs 105-6, Character Pointers and Functions
// Use examples to demonstrate using char pointers in a function

#include <stdio.h>
#include "uart.h"

// strcopy: copy t to s: array subscript version
void strcpy_1(char *s, char *t) 
{
    int8_t i;

    i = 0;
    while((s[i] = t[i]) != '\0')
    {
        i++;
    }
}

// strcopy: copy t to s: pointer version 1
// increment pointers separately
void strcpy_p1(char *s, char *t) 
{

    while((*s = *t) != '\0')
    {
        s++;
        t++;
    }
}

// strcopy: copy t to s: pointer version 2
// move pointer increment into comparison
void strcpy_p2(char *s, char *t) 
{

    while((*s++ = *t++) != '\0')
    {
        ;
    }
}

// strcopy: copy t to s: pointer version 3
// comparison to \0 is redundent,
// as once t contains \0 the expression is false, i.e, (*s = \0)
void strcpy_p3(char *s, char *t) 
{

    while((*s++ = *t++))
    {
        ;
    }
}

int main(void) 
{    
    init_serial();

    puts("\nK&R strcpy Example");
    char *a = "aaaaaa";
    char *b = "b1234b";

    printf("a before: %s\n", a);
    printf("b before: %s\n", b);

    strcpy_p3(a, b);

    printf("a after: %s\n", a);
    printf("b after: %s\n", b);

    return 0;
}
