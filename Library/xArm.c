#include "xArm.h"

char xArm_in[xArm_MAX_BUFFER + 1] = {};
char xArm_out[xArm_MAX_BUFFER + 1] = {};

const char title[] PROGMEM = "\nxArm Commander: Enter commands to interact w xARM";
const char hdr_volt[] PROGMEM = "voltage: ";
const char hdr_pos[] PROGMEM = "Servo position: ";
// const char hdr_temp[] PROGMEM = "Servo Temperature: ";
const char hdr_input[] PROGMEM = "Input entered: ";
const char hdr_cmd_fnd[] PROGMEM = "Command found: ";
const char hdr_cmd_exc[] PROGMEM = "Command executed: ";
const char hdr_cmd_notfnd[] PROGMEM = "Command NOT found: ";
const char hdr_cmd_notimpl[] PROGMEM = "Command NOT implemented: ";
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

char *tokens[MAX_TOKENS];
uint8_t result = 0;
uint8_t joint_no;
uint16_t position;


void init_xArm()
{   
    soft_pgmtext_write(title);
    soft_char_NL();
}

uint8_t lowByte(uint16_t value) {
    return (uint8_t)(value & 0xFF);
}

uint8_t highByte(uint16_t value) {
    return (uint8_t)((value >> 8) & 0xFF);
}

uint16_t xArm_clamp(uint16_t v) {
    return (v < xArm_lo) ? xArm_lo : (xArm_hi < v) ? xArm_hi : v;
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
        soft_pgmtext_write(hdr_cmd_badposition);
        soft_char_NL();
        return -1;
    }
    return p;
}

void echo_command(uint8_t n)
{
    for (uint8_t i = 0; i <= n; i++)
    {
        soft_pgmtext_write(hdr_cmd_exc);
        soft_string_write(tokens[i], strlen(tokens[i]));
        soft_char_space();
    }
    soft_char_NL();
}

void print_error(uint8_t e)
{
  switch (2) 
  {
      case 0:
        soft_pgmtext_write(hdr_cmd_success);
        break;
      case 1:
        soft_pgmtext_write(hdr_cmd_notfnd);
        break;
      case 2:
        soft_pgmtext_write(hdr_cmd_error);
          break;
      
      // command not found
      default:
          echo_command(2);
          result = -1;
          break;
  }

}
// The number of parameters "len" plus a command plus a byte length occupied
// by the data length itself, i.e, Length= len + 2
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

void xArm_beep() {
  xArm_send(CMD_BEEP, 1);
}

uint8_t valid_move(char *j, char *p)
{
    joint_no = valid_joint(j);
    if (joint_no == -1 )
    {
        return joint_no;
    }
    position = valid_position((p));
    if (position == -1 )
    {
        return position;
    }
    xArm_setPosition(joint_no, position);
    return 0;
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

uint16_t xArm_getBatteryVoltage()
{
  xArm_send(CMD_GET_BATTERY_VOLTAGE, 0);
  int8_t results = xArm_recv(CMD_GET_BATTERY_VOLTAGE);
  if (results != -1) {
    return (xArm_in[1] << 8) + xArm_in[0];
  }
  return results;
}

uint8_t printPosition(char *j)
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


// uint16_t xArm_getTemperature(uint8_t servo_id)
// {
//   xArm_out[0] = 1;
//   xArm_out[1] = servo_id;
//   xArm_send(CMD_GET_SERVO_TEMP, 2);
//   int8_t results = xArm_recv(CMD_GET_SERVO_TEMP);
//   if (results != -1) {
//     return (xArm_in[1] << 8) + xArm_in[0];
//   }
//   return results;
// }
