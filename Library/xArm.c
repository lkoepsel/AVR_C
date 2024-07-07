#include "xArm.h"

char xArm_in[xArm_MAX_BUFFER + 1] = {};
char xArm_out[xArm_MAX_BUFFER + 1] = {};

const char title[] PROGMEM = "\nxArm Commander: Enter commands to interact w xARM";
const char hdr_volt[] PROGMEM = "voltage: ";
const char hdr_pos[] PROGMEM = "Servo position: ";
const char hdr_input[] PROGMEM = "Input entered: ";
const char hdr_cmd_fnd[] PROGMEM = "Command found: ";
const char hdr_cmd_rcd[] PROGMEM = "Command received: ";
const char hdr_cmd_notfnd[] PROGMEM = "Command NOT found: ";
const char hdr_cmd_notimpl[] PROGMEM = "Command NOT implemented: ";
const char hdr_cmd_badjoint[] PROGMEM = "Bad joint, must be 1-6";
const char hdr_cmd_badposition[] PROGMEM = "Bad position, must be 1-999";
const char hdr_cmd_success[] PROGMEM = "Success";
const char hdr_cmd_error[] PROGMEM = "Command Error";
const char hdr_cmd_error_parms[] PROGMEM = "Error in parameters";
const char hdr_cmd_error_adds[] PROGMEM = "Moves recorded exceeds limit";
const char hdr_cmd_error_vectors[] PROGMEM = "Vector n specified exceeds limit";
const char hdr_cmd_error_error[] PROGMEM = "Error Error";
const char hdr_cmd_move[] PROGMEM = "move ";
const char debug1[] PROGMEM = "debug:1";
const char debug2[] PROGMEM = "debug:2";
const char debug3[] PROGMEM = "debug:3";
#define debug(n) soft_pgmtext_write(debug##n)

char volt_string[4] = {};
uint8_t volt_len = sizeof(volt_string)/sizeof(volt_string[0]);
char pos_string[4] = {};
uint8_t pos_len = sizeof(pos_string)/sizeof(pos_string[0]);
char temp_string[4] = {};
uint8_t temp_len = sizeof(temp_string)/sizeof(temp_string[0]);
char cmd_string[2] = {};

struct add
{
  uint8_t joint;       // joint to move (1-6)
  uint16_t pos;        // position to move to (1-999)
  uint16_t dur;        // duration of move (0-3000)
  bool wait;           // whether or not to wait until move complete
} ;
struct add adds[N_adds][N_vectors];


char *tokens[MAX_TOKENS];
uint8_t result = 0;
int8_t joint_no;
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

int8_t valid_joint(char *jnt)
{
    uint8_t j = atoi(jnt);
    if ((j < 1) || (j > 6))
    {
        soft_byte_write(atoi(tokens[joint]));
        soft_char_space();
        soft_pgmtext_write(hdr_cmd_badjoint);
        soft_char_NL();
        return -1;
    }
    return j;
}

int16_t valid_position(char *position)
{
    int16_t p = atoi(position);
    if ((p < 1) || (p > 999))
    {
        soft_string_write(tokens[pos], strlen(tokens[pos]));
        soft_char_space();
        soft_pgmtext_write(hdr_cmd_badposition);
        soft_char_NL();
        return -1;
    }
    return p;
}

void echo_command(uint8_t n)
{
    soft_pgmtext_write(hdr_cmd_rcd);
    for (uint8_t i = 0; i <= n; i++)
    {
        soft_string_write(tokens[i], strlen(tokens[i]));
        soft_char_space();
    }
    soft_char_NL();
}

void print_result(uint8_t e)
{
  soft_byte_write(e);
  switch (e) 
  {
      // command successful
      case success:
        soft_pgmtext_write(hdr_cmd_success);
        break;
      
      // command not found
      case notfound:
        soft_pgmtext_write(hdr_cmd_notfnd);
        break;

      // command error
      case badparms:
        soft_pgmtext_write(hdr_cmd_error_parms);
        break;
      
      // command not implemented
      case notimplemented:
        soft_pgmtext_write(hdr_cmd_notimpl);
        break;
      
      // excess_adds - too many moves to record
      case excess_adds:
        soft_pgmtext_write(hdr_cmd_error_adds);
        break;

      // default: error not found
      default:
        soft_pgmtext_write(hdr_cmd_error_error);
        break;
  }

}
// The number of parameters "len" plus command byte plus byte length byte
//  i.e, Length= len + 2
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

uint8_t valid_add(uint8_t i, char *j, char *p)
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
    save_Position(i, joint_no, position);
    return 0;
}

uint8_t show_adds(uint8_t ctr)
{
  for (uint8_t i = 0; i < ctr; i++)
  {
    soft_byte_write(i + 48);
    soft_char_space();
    soft_pgmtext_write(hdr_cmd_move);
    soft_byte_write(adds[i].joint + 48);
    soft_char_space();
    itoa(adds[i].pos, pos_string, 10);
    soft_string_write(pos_string, pos_len);
    soft_char_NL();
  }
  return 0;
}

uint8_t exec_adds(uint8_t ctr)
{
  for (uint8_t i = 0; i < ctr; i++)
  {
    xArm_setPosition(adds[i].joint, adds[i].pos);
    soft_byte_write(i + 48);
    soft_char_space();
    soft_pgmtext_write(hdr_cmd_move);
    soft_byte_write(adds[i].joint + 48);
    soft_char_space();
    itoa(adds[i].pos, pos_string, 10);
    soft_string_write(pos_string, pos_len);
    soft_char_NL();

  }
  return 0;
}

uint8_t reset_adds(uint8_t ctr)
{
  for (uint8_t i = 0; i < ctr; i++)
  {
    adds[i].joint = 0;
    adds[i].pos = 0;
    adds[i].dur = 1000;
    adds[i].wait = true;
  }
  return 0;
}

void save_Position(uint8_t i, uint8_t j, uint16_t p)
{
  uint16_t duration = 1000;
  bool wait = true;

  adds[i].joint = j;
  adds[i].pos = p;
  adds[i].dur = duration;
  adds[i].wait = wait;
  return;
}

void xArm_setPosition(uint8_t servo_id, uint16_t position)
{
  uint16_t duration = 1000;
  bool wait = true;
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

uint8_t print_Voltage()
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

uint8_t print_position(char *j)
{
    joint_no = valid_joint(j);
    if (joint_no == -1 )
    {
        return error;
    }
    uint16_t position = xArm_getPosition(joint_no);
    if (position == -1)
    {
      return error;
    }
    soft_byte_write(*j);
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
