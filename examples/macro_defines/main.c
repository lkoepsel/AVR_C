// macro_defines demonstrates methods for conditional defines
// shows the value for SOFT_RESET in the env.make file
// SOFT_RESET must be defined to any value for successful compilation
#include "unolib.h"
#include <stdio.h>
#include "uart.h"
 
int main(void)
{
    init_serial();

#ifdef SOFT_RESET
    printf("SOFT_RESET is DEFINED and %i\n", SOFT_RESET);

    #if SOFT_RESET == 0
        printf("SOFT_RESET EQUALS 0\n");
    #elif SOFT_RESET == 1
        printf("SOFT_RESET EQUALS 1\n");
    #else
        printf("SOFT_RESET was not defined or equal to 1 or 0\n");
    #endif

    #if !SOFT_RESET
        printf("SOFT_RESET is FALSE\n");
    #elif SOFT_RESET
        printf("SOFT_RESET is TRUE\n");
    #else
        printf("SOFT_RESET was not defined or TRUE or FALSE\n");
    #endif

#else
    printf("SOFT_RESET not defined\n");
#endif

}
