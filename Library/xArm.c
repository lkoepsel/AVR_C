#include "xArm.h"

char xArm_in[xArm_MAX_BUFFER + 1] = {};
char xArm_out[xArm_MAX_BUFFER + 1] = {};

uint8_t lowByte(uint16_t value) {
    return (uint8_t)(value & 0xFF);
}

uint8_t highByte(uint16_t value) {
    return (uint8_t)((value >> 8) & 0xFF);
}

void xArm_send(uint8_t cmd, uint8_t len)
{
    putchar(SIGNATURE);
    putchar(SIGNATURE);
    putchar(len + 2);
    putchar(cmd);
    if (len > 0) 
    {
        for (uint8_t i = 0; i < len; i++)
        {
            putchar(xArm_out[i]);
        }
    }
}

uint8_t xArm_recv(uint8_t cmd)
{
  uint8_t num_char = readLine(xArm_in, 4);
  if (num_char > 0) 
  {
    if (xArm_in[0] == SIGNATURE && xArm_in[1] == SIGNATURE && xArm_in[3] == cmd) {
      int len = xArm_in[2] - 2;
      return readLine(xArm_in, len);
    }
  }
  return -1;
}

uint16_t xArm_clamp(uint16_t v) {
    return (v < xArm_lo) ? xArm_lo : (xArm_hi < v) ? xArm_hi : v;
}

void xArm_setPosition(uint8_t servo_id, uint16_t position)
{
  uint16_t duration = 1000;
  bool wait = false;
  position = xArm_clamp(position);
  xArm_out[0] = 1;
  xArm_out[1] = lowByte(duration);
  xArm_out[2] = highByte(duration);
  xArm_out[3] = servo_id;
  xArm_out[4] = lowByte(position);
  xArm_out[5] = highByte(position);
  xArm_send(CMD_SERVO_MOVE, 6);
  if (wait) {
    delay(duration);
  }
}

// /*** GetPosition ***/

uint16_t xArm_getPosition(uint8_t servo_id)
{
  xArm_out[0] = 1;
  xArm_out[1] = servo_id;
  xArm_send(CMD_GET_SERVO_POSITION, 2);
  int8_t results = xArm_recv(CMD_GET_SERVO_POSITION);
  if (results != -1) 
  {
    return (xArm_in[3] << 8) + xArm_in[2];
  }
  return results;
}


uint16_t xArm_getBatteryVoltage()
{
  xArm_send(CMD_GET_BATTERY_VOLTAGE, 0);
  int8_t results = xArm_recv(CMD_GET_BATTERY_VOLTAGE);
  if (results != -1) {
    return (xArm_in[1] << 8) + xArm_in[0];
  }
  return results;
}

void xArm_beep() {
  xArm_send(CMD_BEEP, 1);
}