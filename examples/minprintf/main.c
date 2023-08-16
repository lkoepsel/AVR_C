#include <stdio.h>  // required for printing
#include "uart.h"   // required for printing
#include <stdarg.h> // required for variable arguments va_

// minprintf - page 156 K&R Second Edition
// minprintf: minimal printf with variable argument list
// with additional comments for clarification

// Many explanations of variable arguments state the last named argument
// must be the count of arguments. This is incorrect, the count may be
// explicit or implicit. This is a implicit example, where the function
// doesn't depend on a count, it exits when it hits the end of a string

void minprintf(char *fmt, ...)
{
    va_list ap;     // arg pointer, will point to each unnamed arg in turn
    char *p;        // will point to each char in fmt
    char *sval;     // will contain the string value if passed
    int ival;       // will contain the integer value if passed
    double dval;    // will contain the double value if passed

    // use the final named argument to get va_ initialized
    // typically, this argument is the count of arguments (explicit)
    // this example, executes til end of arguments available (implicit)
    va_start(ap, fmt);

    // note this loop depends on the last char being a 0, due to the *p
    // as the conditional, loop exits when conditional is false (0)
    for (p = fmt; *p; p++)
    {
        // examine each char in fmt, print if not a %
        if (*p != '%')
        {
            putchar(*p);
            continue;
        }
        // % found, now determine what type of value is arg
        switch(*++p)
        {
        // d - defines the arg as an integer
        case 'd':
             ival = va_arg(ap, int);
             printf("%d", ival);
             break;
        // f - defines the arg as an double
        case 'f':
             dval = va_arg(ap, double);
             printf("%f", dval);
             break;
        // s - defines the arg as a string
        // similar to the fmt loop, the conditional depends on last char as 0
        case 's':
             for (sval = va_arg(ap, char *); *sval; sval++)
             {
                putchar(*sval);
             }
             break;
        // if the desired format is undefined, print format letter and a ?
        default:
            putchar(*p);
            putchar('?');
            break;
        }
    }
    putchar('\n'); // add a new line to make it easy to read
    va_end(ap);     // clean up when done then exit
}

int main(void)
{
    init_serial();      // initialze the serial port

    char string_value[] = {"A new string"};
    char missing_format[] = {"missing format value"};

    minprintf("This is just a string, no formats");
    minprintf("This is a string with an integer format %d", 123);
    minprintf("This is a string with an double format %f", 123.456);
    minprintf("This is a string with another string format %s", string_value);
    minprintf("This is a string with a missing format %g", missing_format);
}
