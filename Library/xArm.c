#include "xArm.h"

char xArm_in[xArm_MAX_BUFFER + 1] = {};
char xArm_out[xArm_MAX_BUFFER + 1] = {};

const char title[] PROGMEM = "\nxArm Commander: Enter commands to interact w xARM";
const char hdr_volt[] PROGMEM = "voltage: ";
const char hdr_save[] PROGMEM = "Vectors saved";
const char hdr_load[] PROGMEM = "Vectors loaded";
const char hdr_pos[] PROGMEM = "Servo position: ";
const char hdr_input[] PROGMEM = "Input entered: ";
const char hdr_cmd_fnd[] PROGMEM = "Command found: ";
const char hdr_cmd_rcd[] PROGMEM = "Command received: ";
const char hdr_cmd_notfnd[] PROGMEM = "Command NOT found: ";
const char hdr_cmd_notimpl[] PROGMEM = "Command NOT implemented: ";
const char hdr_cmd_badjoint[] PROGMEM = "Bad joint, must be 1-";
const char hdr_cmd_badvect[] PROGMEM = "Bad vector, must be 0-";
const char hdr_cmd_vect_0[] PROGMEM = ", vector set to 0";
const char hdr_cmd_badposition[] PROGMEM = "Bad position, must be 1-999";
const char hdr_cmd_success[] PROGMEM = "Success";
const char hdr_cmd_skipped[] PROGMEM = "skpd ";
const char hdr_cmd_error[] PROGMEM = "Command Error";
const char hdr_cmd_error_parms[] PROGMEM = "Error in parameters";
const char hdr_cmd_error_eeprom[] PROGMEM = "Error in EEPROM";
const char hdr_cmd_error_adds[] PROGMEM = "Move to add exceeds limit";
const char hdr_cmd_default_error[] PROGMEM = "Default Error";
const char hdr_cmd_verify_error[] PROGMEM = " EEPROM Vector did not verify";
const char hdr_cmd_move[] PROGMEM = "move ";
const char hdr_cmd_v_col[] PROGMEM = "    v";
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

struct joint
{                     // index serves as joint to move (1-6)
  int16_t pos;        // position to move to (1-999)
  int16_t dur;        // duration of move (0-3000)
  bool wait;          // whether or not to wait until move complete
} ;
struct joint vectors[N_joints][N_vectors];
#define EEPROM 0x0100
uint16_t eeprom_addr;
uint16_t vector_addr;

char *tokens[MAX_TOKENS];
uint8_t result = 0;
int8_t joint_no;
uint16_t position;
int8_t joint_index = 1;
int8_t vect_num = 0;

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

int16_t xArm_clamp(int16_t v) {
    return (v < xArm_lo) ? xArm_lo : (xArm_hi < v) ? xArm_hi : v;
}

int8_t valid_joint(char *jnt)
{
    uint8_t j = atoi(jnt);
    if ((j < 1) || (j > 6))
    {
        soft_byte_write(j + ASCII_INTEGER); 
        soft_char_space();
        soft_pgmtext_write(hdr_cmd_badjoint);
        soft_byte_write(N_joints + ASCII_INTEGER);
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
        soft_string_write(tokens[t_pos], strlen(tokens[t_pos]));
        soft_char_space();
        soft_pgmtext_write(hdr_cmd_badposition);
        soft_char_NL();
        return -1;
    }
    return p;
}

int8_t valid_vector(char *vect)
{
    uint8_t v = (int)strtol(vect, (char **)NULL, 10); 
    if ((v < 0) || (v >= N_vectors ))
    {
        v = 0;
        soft_pgmtext_write(hdr_cmd_badvect);
        soft_byte_write(N_vectors + ASCII_INTEGER - 1);
        soft_pgmtext_write(hdr_cmd_vect_0);
        soft_char_NL();
        return -1;
    }
    // v = atoi(vect);
    return v;
}

void vector_prompt()
{
    int8_t vector_char = vect_num + ASCII_INTEGER;
    soft_byte_write(0x76);
    soft_byte_write(vector_char);
    soft_byte_write(0x3a);
    soft_char_space();
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

      // command bad parameters
      case badparms:
        soft_pgmtext_write(hdr_cmd_error_parms);
        break;
      
      // command not implemented
      case notimplemented:
        soft_pgmtext_write(hdr_cmd_notimpl);
        break;
      
      // excess_adds - too many moves to add
      case excess_adds:
        soft_pgmtext_write(hdr_cmd_error_adds);
        break;

      // eeprom - error in loading/saving EEPROM
      case eeprom:
        soft_pgmtext_write(hdr_cmd_error_eeprom);
        break;

      // default: error not found
      default:
        soft_byte_write(e + ASCII_INTEGER);
        soft_pgmtext_write(hdr_cmd_default_error);
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

int8_t valid_move(char *j, char *p)
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

int8_t valid_add(char *j, char *p)
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
    add_position(joint_no, position);
    return 0;
}

int8_t valid_skip(char *j)
{
    joint_no = valid_joint(j);
    if (joint_no == -1 )
    {
        return joint_no;
    }
    position = 0;
    add_position(joint_no, position);
    return 0;
}

uint8_t show_adds()
{
  for (int8_t i = 0; i < N_vectors; i++)
  {
    joint_index = i + 1;
    soft_pgmtext_write(hdr_cmd_move);
    show_joint(joint_index, vect_num);
    // soft_byte_write(joint_index + 48);
    // soft_char_space();
    // itoa(vectors[i][vect_num].pos, pos_string, 10);
    // soft_string_write(pos_string, pos_len);
    soft_char_NL();
  }
  return 0;
}

uint8_t show_vecs()
{
  for (int8_t i = 0; i < N_vectors; i++)
  { 
    soft_pgmtext_write(hdr_cmd_v_col);
    soft_byte_write(i + ASCII_INTEGER);
    soft_char_space();
    soft_char_space();
    soft_char_space();
    soft_char_space();
  }
  soft_char_NL();
  for (int8_t j = 0; j < N_joints; j++)
  { 
    for (int8_t v = 0; v < N_vectors; v++)
    {
      joint_index = j + 1;
      soft_pgmtext_write(hdr_cmd_move);
      show_joint(joint_index, v);
      soft_char_space();
      soft_char_space();
    }
    soft_char_NL();
  }
  return 0;
}

void show_joint(int8_t j, int8_t v)
{
    soft_byte_write(j + ASCII_INTEGER);
    soft_char_space();
    itoa(vectors[j][v].pos, pos_string, 10);
    soft_string_write(pos_string, pos_len);
    return;
}
uint8_t exec_adds()
{
  for (uint8_t i = 0; i < N_joints; i++)
  {
    joint_index = i + 1;
    if (vectors[i][vect_num].pos == 0)
    {
          soft_pgmtext_write(hdr_cmd_skipped);
    }
    else
    {
    xArm_setPosition(joint_index, vectors[i][vect_num].pos);
    soft_pgmtext_write(hdr_cmd_move);
    }
    show_joint(joint_index, vect_num);
    // soft_byte_write(joint_index + ASCII_JOINT);
    // soft_char_space();
    // itoa(vectors[i][vect_num].pos, pos_string, 10);
    // soft_string_write(pos_string, pos_len);
    soft_char_NL();
  }
  return 0;
}

uint8_t reset_adds()
{
  for (uint8_t i = 0; i < N_joints; i++)
  {
    vectors[i][vect_num].pos = 0;
    vectors[i][vect_num].dur = 1000;
    vectors[i][vect_num].wait = true;
  }
  return 0;
}

void add_position(uint8_t j, uint16_t p)
{
  uint16_t duration = 1000;
  bool wait = true;

  int8_t i = j - 1;     // convert joint to joints index
  vectors[i][vect_num].pos = p;
  vectors[i][vect_num].dur = duration;
  vectors[i][vect_num].wait = wait;
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

int8_t save_vectors()
{
  int8_t r;
  eeprom_addr = EEPROM;
  for (int v = 0; v < N_vectors; v++)
  {
    vector_addr = eeprom_addr;
    for (int j = 0; j < N_joints; j++)
    {
        joint_index = j + 1;
        eeprom_update_word((uint16_t *)(eeprom_addr), vectors[joint_index][v].pos);
        eeprom_addr += sizeof(int16_t);

        eeprom_update_word((uint16_t *)(eeprom_addr), vectors[joint_index][v].dur);
        eeprom_addr += sizeof(int16_t);

        eeprom_update_byte((uint8_t *)(eeprom_addr), vectors[joint_index][v].wait);
        eeprom_addr += sizeof(bool);
    }
      r = verify_vectors(v, vector_addr);
    if (r == -1)
    {
      return eeprom;
    }
  }
    soft_pgmtext_write(hdr_save);
    soft_char_NL();
    return 0;
}

int8_t load_vectors()
{
    int8_t r;
    eeprom_addr = EEPROM;
    for (int v = 0; v < N_vectors; v++)
  {
    vector_addr = eeprom_addr;
    for (int j = 1; j < N_joints; j++)
    {
        joint_index = j + 1;
        vectors[joint_index][v].pos = eeprom_read_word((uint16_t *)(eeprom_addr));
        eeprom_addr += sizeof(int16_t);

        vectors[joint_index][v].dur = eeprom_read_word((uint16_t *)(eeprom_addr));
        eeprom_addr += sizeof(int16_t);

        vectors[joint_index][v].wait = eeprom_read_byte((uint8_t *)(eeprom_addr));
        eeprom_addr += sizeof(bool);
    }
    r = verify_vectors(v, vector_addr);
    if (r == -1)
    {
      return eeprom;
    }
  }
    return r;
}

int8_t verify_vectors(int8_t v, uint16_t addr)
{
  bool verify = TRUE;
  eeprom_addr = addr;
  int16_t p;
  int16_t d;
  bool w;
    for (int j = 1; j < N_joints; j++)
    {
        joint_index = j + 1;
        p = eeprom_read_word((uint16_t *)(eeprom_addr));
        if (p != vectors[joint_index][v].pos)
        {
          verify = FALSE;
        }
        eeprom_addr += sizeof(int16_t);

        d = eeprom_read_word((uint16_t *)(eeprom_addr));
        if (d != vectors[joint_index][v].dur)
        {
          verify = FALSE;
        }
        eeprom_addr += sizeof(int16_t);

        w = eeprom_read_byte((uint8_t *)(eeprom_addr));
        if (w != vectors[joint_index][v].wait)
        {
          verify = FALSE;
        }
        eeprom_addr += sizeof(bool);
  }
    if (!verify)
    {
        soft_byte_write(v + ASCII_INTEGER);
        soft_pgmtext_write(hdr_cmd_verify_error);
        soft_char_NL();
        return -1;
    }
    else
    {
        soft_pgmtext_write(hdr_load);
        soft_char_NL();
        return 0;
    }
}

uint8_t print_voltage()
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

int8_t print_position(char *j)
{
    joint_no = valid_joint(j);
    if (joint_no == -1 )
    {
        return badparms;
    }
    uint16_t position = xArm_getPosition(joint_no);
    if (position == -1)
    {
      return badparms;
    }
    soft_byte_write(*j);
    soft_char_space();
    itoa(position, pos_string, 10);
    soft_pgmtext_write(hdr_pos);
    soft_string_write(pos_string, pos_len);
    soft_char_NL();
    return 0;
}

int8_t get_vect_num(char *v)
{
    vect_num = valid_vector(v);
    if (vect_num == -1 )
    {
        vect_num = 0;
        return badparms;
    }
    // soft_byte_write(*v);
    // soft_char_space();
    // soft_char_NL();
    return 0;
}

uint8_t show_pos()
{
  for (uint8_t i = 0; i < N_joints; i++)
  {
    char j_c = i + 0x2f;
    print_position(&j_c);
  }
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
