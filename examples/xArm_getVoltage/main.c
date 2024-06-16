// xArm getVoltage
// Change baud rate in env.make to 9600 to match xArm
// 
// 
 
#include <stdio.h>
#include "xArm.h"
#include "uart.h"

int main(void) 
{    

    init_serial();
    init_soft_serial();

    puts("xArm Test: Use soft_readLine to get voltage");
    int voltage = xArm_getBatteryVoltage();
    printf("voltage %i", voltage);

}
