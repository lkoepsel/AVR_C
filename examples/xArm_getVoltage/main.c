// xArm getVoltage
// Change baud rate in env.make to 9600 to match xArm
// 
// 
 
#include <stdio.h>
#include "xArm.h"
#include "uart.h"
#include "soft_serial.h"

char title[40] = {"xArm Test: Use UART to get voltage"};
uint8_t title_len = sizeof(title)/sizeof(title[0]);
char sub[10] = {"voltage "};
uint8_t sub_len = sizeof(sub)/sizeof(sub[0]);
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
    soft_string_write(sub, sub_len);
    soft_string_write(volt_string, volt_len);
    soft_char_NL();
}
