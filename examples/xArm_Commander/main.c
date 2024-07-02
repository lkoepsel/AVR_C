// xArm Commander
// Change baud rate in env.make to 9600 to match xArm
// UNO 0/1 (uart) - connect to xARM, RX/TX
// UNO 2/3 (soft_serial) - connect to FTDI/USB converter to RPi, RX/TX
// Uno sends commands to xARM via 0/1
// UNO accepts commands/prints responses from xArm via 2/3
// use tio -l to determine which /dev is connected to FTDI
// use tio /dev/{name} to connect to FTDI i.e; /dev/ttyUSB0
 
#include <stdio.h>
#include <string.h>
#include "xArm.h"
#include "uart.h"
#include "soft_serial.h"


#define NUM_COMMANDS 6
#define MAX_CMD_LENGTH 6 // # of characters + null terminator

enum {cmd, joint, pos};

const char commands[NUM_COMMANDS][MAX_CMD_LENGTH] = 
{
    "move",
    "pos",
    "off",
    "reset",
    "volt",
    "beep"
};

char* tokenLine(char *input)
{
    // break input line into tokens
    // when this section has executed, the characters in input
    // which were separated by a delim
    // will now be a pointer called tokens
    // with each index, a multiple character token
    char delim[MAX_DELIMS + 1] = {" "};

    uint8_t index = 0;
    tokens[index] = strtok(input, delim);
    while ( (tokens[index] != NULL) && (index < MAX_TOKENS - 1) ) 
    {
        index++;
        tokens[index] = strtok(NULL, delim);
    }
    return *tokens;
}

int command_to_int(const char *command) 
{
    for (uint8_t i = 0; i < NUM_COMMANDS; ++i) {
        if (strcmp(command, commands[i]) == 0) {
            return i + 1; // Return 1-based index
        }
    }
    return -1; // Invalid command
}

// uint8_t getTemperature(uint8_t j)
// {
//     uint16_t temperature = xArm_getTemperature(j);
//     if (temperature == -1)
//     {
//         return temperature;
//     }
//     char str_j = j + 48;
//     soft_byte_write(str_j);
//     soft_char_space();
//     itoa(position, temp_string, 10);
//     soft_pgmtext_write(hdr_temp);
//     soft_string_write(temp_string, temp_len);
//     soft_char_NL();
//     return 0;
// }


int main(void) 
{    
    init_serial();
    init_soft_serial();
    init_xArm();

    // input is the buffer for the serial port
    char input[MAX_BUFFER + 1] = {};

    while (1) 
    {
        // get input, use first token as command
        soft_readLine(input, MAX_BUFFER);
        tokenLine(input);
        int command_id = command_to_int(tokens[cmd]);
        uint8_t result = 0;

        switch (command_id) 
        {
            // move joint position
            case 1:
                echo_command(pos);
                result = valid_move(tokens[joint], tokens[pos]);
                break;
            
            // pos joint
            case 2:
                echo_command(joint);
                result = print_position(tokens[joint]);
                break;
            
            // off
            case 3:
                echo_command(joint);
                result = 0;
                break;
            
            // reset
            case 4:
                echo_command(joint);
                result = 0;
                break;
            
            // temp joint
            // case 5:
            //     echo_command(joint);

            //     uint8_t tj = (uint8_t) *tokens[joint] - 48;
            //     result = getTemperature(tj);
            //     break;
            
            // volt - get the battery voltage
            case 6:
                echo_command(cmd);
                result = printVoltage();
                break;
            
            // beep - make arm beep
            case 7:
                echo_command(cmd);
                xArm_beep();
                result = 0;
                break;
            
            // command not found
            default:
                echo_command(pos);
                result = -1;
                break;
        }
        if (result != 0)
        {
            print_error(2);
        }
        else
        {
            print_error(0);
        }
        soft_char_NL();

        // clear input buffer for next command
        for (uint8_t i=0; i<MAX_BUFFER; i++)
        {
            input[i] = ' ';
        }
    }
    return 0;
}
