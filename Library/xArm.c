#include "xArm.h"

char xArm_in[xArm_MAX_BUFFER + 1] = {};
char xArm_out[xArm_MAX_BUFFER + 1] = {};


void xArm_send(int cmd, int len)
{
    putchar(SIGNATURE);
    putchar(SIGNATURE);
    putchar(len + 2);
    putchar(cmd);
    if (len > 0) 
    {
        for (uint8_t i = 0; i <= len; i++)
        {
            putchar(xArm_out[i]);
        }
    }
}

int xArm_recv(int cmd)
{
  if (-1 != readLine(xArm_in, 4)) {
    if (xArm_in[0] == SIGNATURE && xArm_in[1] == SIGNATURE && xArm_in[3] == cmd) {
      int len = xArm_in[2] - 2;
      return readLine(xArm_in, len);
    }
  }
  return -1;
}

int xArm_getBatteryVoltage()
{
  xArm_send(CMD_GET_BATTERY_VOLTAGE, 0);
  if (-1 != xArm_recv(CMD_GET_BATTERY_VOLTAGE)) {
    return (xArm_in[1] << 8) + xArm_in[0];
  }
  return -1;
}
