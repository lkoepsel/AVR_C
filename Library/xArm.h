// xArm getVoltage
// Change baud rate in env.make to 9600 to match xArm
// 
// 

#ifndef XARM_H
#define XARM_H

#include <stdio.h>
#include "uart.h"
#include <string.h>
#include "readLine.h"


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

#define xArm_MAX_BUFFER 32
extern char xArm_in[xArm_MAX_BUFFER + 1];
extern char xArm_out[xArm_MAX_BUFFER + 1];

void xArm_send(int cmd, int len);

int xArm_recv(int cmd);

int xArm_getBatteryVoltage();

#endif