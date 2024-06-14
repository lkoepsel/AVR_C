// xArm getVoltage
// Change baud rate in env.make to 9600 to match xArm
// 
// 
 
#include <stdio.h>
#include "xArm.h"

int main(void) {    

    init_serial();
    int voltage = xArm_getBatteryVoltage();
    printf("voltage %i", voltage);

}
