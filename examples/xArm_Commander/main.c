// xArm Commander
// Change baud rate in env.make to 9600 to match xArm
// UNO 0/1 - connect to xARM, RX/TX
// UNO 2/3 - connect to FTDI/USB converter to RPi, RX/TX
// Uno sends commands to xARM via 0/1
// UNO accepts commands/prints responses from xArm via 2/3
// use tio -l to determine which /dev is connected to FTDI
// use tio /dev/{name} to connect i.e; /dev/ttyUSB0
 
#include <stdio.h>
#include "xArm.h"
#include "uart.h"
#include "soft_serial.h"

char title[50] = {"xArm Commander: Enter commands to interact w xARM"};
uint8_t title_len = sizeof(title)/sizeof(title[0]);
char sub_volt[10] = {"voltage "};
uint8_t sub_len = sizeof(sub_volt)/sizeof(sub_volt[0]);
char volt_string[4] = {};
uint8_t volt_len = sizeof(volt_string)/sizeof(volt_string[0]);

int main(void) 
{    
    init_serial();
    init_soft_serial();

    soft_string_write(title, title_len);
    soft_char_NL();
    int voltage = xArm_getBatteryVoltage();
    itoa(voltage, volt_string, 10);
    soft_string_write(sub_volt, sub_len);
    soft_string_write(volt_string, volt_len);
    soft_char_NL();
}
