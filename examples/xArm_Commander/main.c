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
char hdr_volt[10] = {"voltage "};
uint8_t sub_len = sizeof(hdr_volt)/sizeof(hdr_volt[0]);
char volt_string[4] = {};
uint8_t volt_len = sizeof(volt_string)/sizeof(volt_string[0]);

#define NUM_COMMANDS 4
#define MAX_CMD_LENGTH 6 // 5 characters + null terminator
const char commands[NUM_COMMANDS][MAX_CMD_LENGTH] = 
{
    "move",
    "reset",
    "pos",
    "volt"
};

int command_to_int(const char *command) 
{
    for (uint8_t i = 0; i < NUM_COMMANDS; ++i) {
        if (strcmp(command, commands[i]) == 0) {
            return i + 1; // Return 1-based index
        }
    }
    return -1; // Invalid command
}

void printVoltage()
{
    int voltage = xArm_getBatteryVoltage();
    itoa(voltage, volt_string, 10);
    soft_string_write(hdr_volt, sub_len);
    soft_string_write(volt_string, volt_len);
    soft_char_NL();
}

int main(void) 
{    
    init_serial();
    init_soft_serial();

    soft_string_write(title, title_len);
    soft_char_NL();

    int command_id = command_to_int("volt");

    switch (command_id) 
    {
        case 1:
            printf("move executed.\n");
            break;
        case 2:
            printf("reset executed.\n");
            break;
        case 3:
            printf("pos executed.\n");
            break;
        case 4:
            printVoltage();
            break;
        default:
            printf("Invalid command.\n");
            break;
    }
    return 0;
}
