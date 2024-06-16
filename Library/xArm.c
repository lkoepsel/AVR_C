#include "xArm.h"

char xArm_in[xArm_MAX_BUFFER + 1] = {};
char xArm_out[xArm_MAX_BUFFER + 1] = {};

void xArm_send(int cmd, int len)
{
    soft_char_write(SIGNATURE);
    soft_char_write(SIGNATURE);
    soft_char_write(len + 2);
    soft_char_write(cmd);
    if (len > 0) 
    {
        for (uint8_t i = 0; i <= len; i++)
        {
            soft_char_write(xArm_out[i]);
        }
    }
}

int xArm_recv(int cmd)
{
  puts("execute soft_readline");
  uint8_t num_char = soft_readLine(xArm_in, 4);
  printf("num_char: %i", num_char);
  if (num_char > 0) 
  {
    if (xArm_in[0] == SIGNATURE && xArm_in[1] == SIGNATURE && xArm_in[3] == cmd) {
      int len = xArm_in[2] - 2;
      return soft_readLine(xArm_in, len);
    }
  }
  return -1;
}

int xArm_getBatteryVoltage()
{
  puts("send command");
  xArm_send(CMD_GET_BATTERY_VOLTAGE, 0);
  puts("recv voltage");
  int8_t results = xArm_recv(CMD_GET_BATTERY_VOLTAGE);
  printf("results: %i", results);
  if (results != -1) {
    return (xArm_in[1] << 8) + xArm_in[0];
  }
  return results;
}
