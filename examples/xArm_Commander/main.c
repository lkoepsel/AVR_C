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

const char title[] PROGMEM = "\nxArm Commander: Enter commands to interact w xARM";
const char hdr_volt[] PROGMEM = "voltage: ";
const char hdr_pos[] PROGMEM = "Servo position: ";
const char hdr_temp[] PROGMEM = "Servo Temperature: ";
const char hdr_input[] PROGMEM = "Input entered: ";
const char hdr_cmd_fnd[] PROGMEM = "Command found: ";
const char hdr_cmd_exc[] PROGMEM = "Command executed: ";
const char hdr_cmd_notfnd[] PROGMEM = "Command NOT found: ";
const char hdr_cmd_notimpl[] PROGMEM = "Command NOT implemented: ";
const char hdr_cmd_beep[] PROGMEM = "beep";
const char hdr_cmd_badjoint[] PROGMEM = "Bad joint, must be 1-6";
const char hdr_cmd_badposition[] PROGMEM = "Bad position, must be 1-999";
const char hdr_cmd_success[] PROGMEM = "Success";
const char hdr_cmd_error[] PROGMEM = "Error";

char volt_string[4] = {};
uint8_t volt_len = sizeof(volt_string)/sizeof(volt_string[0]);
char pos_string[4] = {};
uint8_t pos_len = sizeof(pos_string)/sizeof(pos_string[0]);
char temp_string[4] = {};
uint8_t temp_len = sizeof(temp_string)/sizeof(temp_string[0]);
char cmd_string[2] = {};

#define MAX_BUFFER 24
#define MAX_TOKENS (MAX_BUFFER/2)
#define MAX_DELIMS 1
char *tokens[MAX_TOKENS];

#define NUM_COMMANDS 7
#define MAX_CMD_LENGTH 6 // # of characters + null terminator

enum {cmd, joint, pos};
uint8_t joint_no;
uint16_t position;

const char commands[NUM_COMMANDS][MAX_CMD_LENGTH] = 
{
    "move",
    "pos",
    "off",
    "reset",
    "temp",
    "volt",
    "beep"
};

char* tokenLine(char *input)
{
    // break input line into tokens
    // when this section has executed, the characters in input
    // which are separated by a delim
    // will now be a pointer called tokens
    // with each index, a multiple character token
    char delim[MAX_DELIMS + 1] = {" "};

    uint8_t index = 0;
    tokens[index] = strtok(input, delim);
    while ( (tokens[index] != NULL) && (index < MAX_TOKENS - 1) ) {
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

uint8_t valid_joint(char *joint)
{
    uint8_t jnt = atoi(joint);
    if ((jnt < 1) || (jnt > 6))
    {
        soft_pgmtext_write(hdr_cmd_badjoint);
        soft_char_NL();
        return -1;
    }
    return jnt;
}

uint8_t valid_position(char *pos)
{
    uint8_t p = atoi(pos);
    if ((p < 1) || (p > 6))
    {
        soft_pgmtext_write(hdr_cmd_badjoint);
        soft_char_NL();
        return -1;
    }
    return p;
}

uint8_t move(char *j, char *d)
{
    joint_no = valid_joint(j);
    if (joint_no == -1 )
    {
        return joint_no;
    }
    position = valid_position((d));
    if (position == -1 )
    {
        return position;
    }
    xArm_setPosition(joint_no, position);
    return 0;
}

uint8_t getPosition(char *j)
{
    joint_no = valid_joint(j);
    if (joint_no == -1 )
    {
        return joint_no;
    }
    uint16_t position = xArm_getPosition(joint_no);
    if (position == -1)
    {
        return position;
    }
    char str_j = joint_no + 48;
    soft_char_write(str_j);
    soft_char_space();
    itoa(position, pos_string, 10);
    soft_pgmtext_write(hdr_pos);
    soft_string_write(pos_string, pos_len);
    soft_char_NL();
    return 0;
}

uint8_t getTemperature(uint8_t j)
{
    uint16_t temperature = xArm_getTemperature(j);
    if (temperature == -1)
    {
        return temperature;
    }
    char str_j = j + 48;
    soft_char_write(str_j);
    soft_char_space();
    itoa(position, temp_string, 10);
    soft_pgmtext_write(hdr_temp);
    soft_string_write(temp_string, temp_len);
    soft_char_NL();
    return 0;
}

uint8_t printVoltage()
{
    int voltage = xArm_getBatteryVoltage();
    if (voltage == -1)
    {
        return voltage;
    }
    itoa(voltage, volt_string, 10);
    soft_pgmtext_write(hdr_volt);
    soft_string_write(volt_string, volt_len);
    soft_char_NL();
    return 0;
}

int main(void) 
{    
    init_serial();
    init_soft_serial();

    // input is the buffer for the serial port
    char input[MAX_BUFFER + 1] = {};

    // write command request to soft serial
    soft_pgmtext_write(title);
    soft_char_NL();

    // DEBUG: get input and echo back to soft serial
    // uncomment this line and comment comparable soft_readLine() below
    // uint8_t num_char = soft_readLine(input, MAX_BUFFER);
    // soft_pgmtext_write(hdr_input);
    // soft_string_write(input, num_char);
    // soft_char_NL();

    while (1) 
    {
        // get input, use first token as command
        soft_readLine(input, MAX_BUFFER);
        tokenLine(input);
        int command_id = command_to_int(tokens[cmd]);
        char str_command = command_id + 48;
        uint8_t result = 0;

        switch (command_id) 
        {
            // move joint position
            case 1:
                soft_pgmtext_write(hdr_cmd_exc);
                soft_string_write(tokens[cmd], strlen(tokens[cmd]));
                soft_char_space();
                soft_string_write(tokens[joint], strlen(tokens[joint]));
                soft_char_space();
                soft_string_write(tokens[pos], strlen(tokens[pos]));
                soft_char_NL();
                result = move(tokens[joint], tokens[pos]);
                break;
            
            // pos joint
            case 2:
                soft_pgmtext_write(hdr_cmd_exc);
                soft_string_write(tokens[cmd], strlen(tokens[cmd]));
                soft_char_space();
                soft_string_write(tokens[joint], strlen(tokens[joint]));
                soft_char_NL();

                // uint8_t pj = (uint8_t) *tokens[joint] - 48;
                result = getPosition(tokens[pos]);
                break;
            
            // off
            case 3:
                soft_pgmtext_write(hdr_cmd_exc);
                soft_string_write(tokens[cmd], strlen(tokens[cmd]));
                soft_char_space();
                soft_string_write(tokens[joint], strlen(tokens[joint]));
                soft_char_NL();
                result = 0;
                break;
            
            // reset
            case 4:
                soft_pgmtext_write(hdr_cmd_exc);
                soft_string_write(tokens[cmd], strlen(tokens[cmd]));
                soft_char_space();
                soft_string_write(tokens[joint], strlen(tokens[joint]));
                soft_char_NL();
                result = 0;
                break;
            
            // temp joint
            case 5:
                soft_pgmtext_write(hdr_cmd_exc);
                soft_string_write(tokens[cmd], strlen(tokens[cmd]));
                soft_char_space();
                soft_string_write(tokens[joint], strlen(tokens[joint]));
                soft_char_NL();

                uint8_t tj = (uint8_t) *tokens[joint] - 48;
                result = getTemperature(tj);
                break;
            
            // volt - get the battery voltage
            case 6:
                result = printVoltage();
                break;
            
            // beep - make arm beep
            case 7:
                xArm_beep();
                soft_pgmtext_write(hdr_cmd_beep);
                soft_char_NL();
                result = 0;
                break;
            
            // command not found
            default:
                soft_char_write(str_command);
                soft_pgmtext_write(hdr_cmd_notfnd);
                result = -1;
                break;
        }
        if (result != 0)
        {
            soft_pgmtext_write(hdr_cmd_error);
        }
        else
        {
            soft_pgmtext_write(hdr_cmd_success);
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
