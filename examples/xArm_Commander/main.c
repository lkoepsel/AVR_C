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
#include "delay.h"

// tokenLine - break arg:input into tokens
// on entry arg:input has tokens each separated by a delim, defined below
// on return: tokens contains pointers to a legal string for each token
// ex: token[0] is a pointer to the first string
char *tokenLine(char *input)
{
    char delim[MAX_DELIMS + 1] = {" "};

    uint8_t index = 0;
    tokens[index] = strtok(input, delim);
    while ((tokens[index] != NULL) && (index < MAX_TOKENS - 1))
    {
        index++;
        tokens[index] = strtok(NULL, delim);
    }
    return *tokens;
}

// define the available commands for controlling the xArm
// command is converted into an int then used in execute_cmd()
#define MAX_CMD_LENGTH 6 // # of characters + null terminator
const char commands[N_COMMANDS][MAX_CMD_LENGTH] =
    {
        "help",
        "move",
        "pos",
        "add",
        "skip",
        "show",
        "vecs",
        "exec",
        "reset",
        "all",
        "perf",
        "vect",
        "save",
        "load",
        "volt",
        "beep"};
enum cmd_values
{
    help,
    move,
    posn,
    add,
    skip,
    show,
    vecs,
    exec,
    reset,
    all,
    perf,
    vect,
    save,
    load,
    volt,
    beep
};

int command_to_int(const char *command)
{
    for (uint8_t i = 0; i < N_COMMANDS; ++i)
    {
        if (strcmp(command, commands[i]) == 0)
        {
            return i;
        }
    }
    return -1; // Invalid command
}

uint8_t execute_cmd(uint8_t c_id)
{
    int8_t r = 0;
    switch (c_id)
    {
    // help - print help menu
    case help:
        // echo_command(t_cmd);
        print_help();
        break;

    // move joint position
    case move:
        echo_command(t_pos);
        r = valid_move(tokens[t_joint], tokens[t_pos]);
        break;

    // pos joint
    case posn:
        echo_command(t_joint);
        r = print_position(tokens[t_joint]);
        break;

    // add a joint position for playback
    case add:
        echo_command(t_pos);
        r = valid_add(tokens[t_joint], tokens[t_pos]);
        break;

    // skip (or delete) a joint position for playback
    case skip:
        echo_command(t_joint);
        r = valid_skip(tokens[t_joint]);
        break;

    // show moves which have been added
    case show:
        echo_command(t_joint);
        r = show_adds();
        break;

    // show list of vectors
    case vecs:
        echo_command(t_joint);
        r = show_vecs();
        break;

    // executes moves which have been added
    case exec:
        echo_command(t_joint);
        r = exec_adds();
        break;

    // reset
    case reset:
        echo_command(t_joint);
        r = reset_adds();
        break;

    // all
    case all:
        echo_command(t_joint);
        r = show_all();
        break;

    // perf
    case perf:
        echo_command(t_joint);
        r = perf_all();
        break;

    // vect - get the current vector number
    case vect:
        echo_command(t_joint);
        r = get_vect_num(tokens[t_joint]);
        break;

    // save - save all of the vectors to EEPROM
    case save:
        echo_command(t_cmd);
        r = save_vectors();
        break;

    // load - load all of the vectors from EEPROM
    case load:
        echo_command(t_cmd);
        r = load_vectors();
        break;

    // volt - get the battery voltage
    case volt:
        echo_command(t_cmd);
        r = print_voltage();
        break;

    // beep - make arm beep
    case beep:
        echo_command(t_cmd);
        xArm_beep();
        r = 0;
        break;

    // command not found
    default:
        echo_command(t_pos);
        r = 1;
        break;
    }

    if (r == -1)
    {
        r = badparms;
    }
    return r;
}

int main(void)
{
    // UART is used to communicate with xArm
    // soft_serial is used to communicate with user
    init_serial();
    init_soft_serial();
    // sei(); // Enable global interrupts
    // delay(500);
    init_xArm();

    // input is the buffer for the soft_serial port
    char input[MAX_BUFFER + 1] = {};

    while (1)
    {
        // get input, use first token as command
        soft_readLine(input, MAX_BUFFER);
        tokenLine(input);
        uint8_t command_id = command_to_int(tokens[t_cmd]);

        uint8_t result = execute_cmd(command_id);
        print_result(result);
        soft_char_NL();
        vector_prompt();

        // clear input buffer for next command
        for (uint8_t i = 0; i < MAX_BUFFER; i++)
        {
            input[i] = ' ';
        }
    }
    return 0;
}
