// xArm ServoController C99 version
// Copied from https://github.com/ccourson/xArmServoController
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
#include "readLine.h"
#include "uart.h"
#include "delay.h"

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

// replace modal clamp limits, as this is only for xArm
#define xArm_lo 0 
#define xArm_hi 1000

struct xArmServo {
    uint8_t servo_id;
    uint16_t position;
};

#define xArm_MAX_BUFFER 32
extern char xArm_in[xArm_MAX_BUFFER + 1];
extern char xArm_out[xArm_MAX_BUFFER + 1];

// void setPosition(uint8_t servo_id, uint16_t position, uint16_t duration = 1000, bool wait = false);
// void setPosition(xArmServo servo, uint16_t duration = 1000, bool wait = false);
// void setPosition(xArmServo servos[], uint8_t count, uint16_t duration = 1000, bool wait = false);

// uint16_t getPosition(uint8_t servo_id);
// uint16_t getPosition(xArmServo &servo);
// bool getPosition(xArmServo servos[], uint8_t count);

// void servoOff(uint8_t servo_id);
// void servoOff(int num, uint8_t servo_id, ...);
// void servoOff(xArmServo servo);
// void servoOff(xArmServo servos[], uint8_t count);
// void servoOff();

// void actionRun(uint8_t group, uint8_t times = 1);
// void actionStop();
// void actionSpeed(uint8_t group, uint8_t percent);
// bool actionIsRunning();
// bool serialEvent();

uint8_t lowByte(uint16_t value);
uint8_t highByte(uint16_t value);
uint16_t xArm_getBatteryVoltage();
void xArm_beep();

// bool actionRunning;

uint16_t clamp(uint16_t v);
void xArm_setPosition(uint8_t servo_id, uint16_t position);
void xArm_send(uint8_t cmd, uint8_t len);
uint8_t xArm_recv(uint8_t cmd);

#endif