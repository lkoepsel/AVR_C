// xArm ServoController C99 version
// Some aspects copied from https://github.com/ccourson/xArmServoController
// 
//   xArmServoController.h - Library for controlling xArm servos.
//   Version 1.0.0
//   Created by Chris Courson, July 9, 2020.
// 

#ifndef XARM_H
#define XARM_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "delay.h"
#include "readLine.h"
#include "soft_serial.h"
#include "uart.h"

#define SIGNATURE               0x55
#define CMD_BEEP                0x00
#define CMD_SERVO_MOVE          0x03
#define CMD_ACTION_GROUP_RUN    0x06
#define CMD_ACTION_GROUP_STOP   0x07
#define CMD_ACTION_GROUP_END    0x08
#define CMD_ACTION_GROUP_SPEED  0x0B
#define CMD_GET_BATTERY_VOLTAGE 0x0f
#define CMD_SERVO_STOP          0x14
#define CMD_GET_SERVO_POSITION  0x15
#define CMD_GET_SERVO_LOADS     0x16
#define CMD_GET_SERVO_TEMP      0x1b
#define CMD_GET_SERVO_VOLTAGE   0x1a

#define MAX_BUFFER 24
#define MAX_TOKENS (MAX_BUFFER/2)
#define MAX_DELIMS 1
#define N_joints 6
#define N_vectors 10
#define N_COMMANDS 16

extern char *tokens[MAX_TOKENS];

// use the labels below to results for printing
// 0 is success, 1 is command not found...
enum {success, xArm, notfound, badparms, notimplemented, excess_adds, eeprom, error};

// use the labels below to reference the string parameters in tokens
// tokens[t_cmd] is the command, tokens[t_joint] is the joint...
enum {t_cmd, t_joint, t_pos};

// replace modal clamp limits, as this is only for xArm
#define xArm_lo 1 
#define xArm_hi 1000

#define xArm_MAX_BUFFER 32
extern char xArm_in[xArm_MAX_BUFFER + 1];
extern char xArm_out[xArm_MAX_BUFFER + 1];

void init_xArm();
void print_help();

void echo_command(uint8_t n);
void vector_prompt();
void print_result(uint8_t e);


uint8_t lowByte(uint16_t value);
uint8_t highByte(uint16_t value);
int16_t xArm_clamp(int16_t v);

int8_t valid_joint(char *joint);
int16_t valid_position(char *pos);
int8_t valid_vector(char *vect);

void xArm_send(uint8_t cmd, uint8_t len);
uint8_t xArm_recv(uint8_t cmd);

void xArm_beep();
int8_t valid_move(char *j, char *p);
int8_t valid_add(char *j, char *p);
int8_t valid_skip(char *j);
uint8_t show_adds();
uint8_t show_vecs();
void show_joint_pos(int8_t j, int8_t v);
uint8_t exec_adds();
uint8_t reset_adds();
void add_position();
void xArm_setPosition(uint8_t servo_id, int16_t position);
int8_t save_vectors();
int8_t load_vectors();
int8_t verify_vectors(int8_t v, uint16_t addr);
uint8_t print_voltage();
uint16_t xArm_getBatteryVoltage();
int8_t print_position(char *j);
int8_t get_vect_num(char *v);
uint8_t show_all();
int8_t perf_all();
uint16_t xArm_getPosition(uint8_t servo_id);

#endif