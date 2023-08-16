// Serial I/O Wrap Print - Add timestamps to every printf() call
// Use a feature of the GNU linker to ‘wrap’ around any symbol or function,
// including the ones in the standard library. For example, add to the printf()
// a wrapper, which adds a timestamp for every call.
// [GNU Linker Wizardry: Wrapping printf() with Timestamps | MCU on Eclipse]
// (https://mcuoneclipse.com/2023/07/22/gnu-linker-wizardry-wrapping-printf-with-timestamps/)
// [Variable Argument Lists in C using va_list]
// (https://www.cprogramming.com/tutorial/c/lesson17.html)
// Use __real_printf() for calls w/o timestamp
// Uncomment line: LDFLAGS += -Wl,--wrap=printf in main Makefile
 
#include <stdio.h>
#include <stdarg.h>
#include "sysclock.h"
#include "uart.h"

// uses CR as end of line, might need to be changed to LF
#define CR 13

uint16_t __real_printf(const char *fmt, ...);

uint16_t __wrap_printf(const char *fmt, ...) 
{
  va_list args;
  uint16_t count0, count1;
  count0 = __real_printf("%ld", millis());
  va_start(args, fmt);
  count1 = vprintf(fmt, args);
  va_end(args);
  return count0+count1;
}

int main(void) 
{    
    init_serial();
    init_sysclock_2 ();

    char input;

    __real_printf("printf wrapper Example\n");
    __real_printf("Press any key to show elapsed time(ms)\n");
    __real_printf("Press Return to exit program\n");
    while((input = getchar())!= CR) 
    {
        printf(" ms since reset, %c key pressed\n", input);
    }
    __real_printf("Program Exit\n");
}
