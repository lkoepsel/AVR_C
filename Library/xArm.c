#include "xArm.h"

char xArm_in[xArm_MAX_BUFFER + 1] = {};
char xArm_out[xArm_MAX_BUFFER + 1] = {};

const char title[] PROGMEM = "xArm Commander: Enter commands to interact w xARM, enter help to see commands";
const char hdr_volt[] PROGMEM = "voltage: ";
const char hdr_save[] PROGMEM = "Vectors saved";
const char hdr_verified[] PROGMEM = "Vector verified";
const char hdr_pos[] PROGMEM = "Servo position: ";
const char hdr_input[] PROGMEM = "Input entered: ";
const char hdr_cmd_fnd[] PROGMEM = "Command found: ";
const char hdr_cmd_rcd[] PROGMEM = "Command received: ";
const char hdr_cmd_xArm[] PROGMEM = "xArm has an error ";
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
const char hdr_cmd_v_col[] PROGMEM = "v";

const char help_0[] PROGMEM = "help     - print this menu";
const char help_1[] PROGMEM = "move j p - move j (joint 1-6) to p (position 1 - 999)";
const char help_2[] PROGMEM = "pos j    - return the position of j (joint 1-6)";
const char help_3[] PROGMEM = "vect v   - set the active vector to v (vector 0-9), vn: prompt shows current vector";
const char help_4[] PROGMEM = "add j p  - similar as move, except adds to active vector move list";
const char help_5[] PROGMEM = "show     - show active vector move list";
const char help_6[] PROGMEM = "vecs     - show complete matrix of moves, each joint is a line and each column is a vector";
const char help_7[] PROGMEM = "perf     - perform all 10 vectors (0-9) with a one second delay between each vector move";
const char help_8[] PROGMEM = "exec     - execute active vector move list";
const char help_9[] PROGMEM = "reset    - reset all active vector moves to 0";
const char help_10[] PROGMEM = "all      - show all positions of servos";
const char help_11[] PROGMEM = "save     - save all vectors to EEPROM all vectors, verified on save";
const char help_12[] PROGMEM = "load     - load all vectors from EEPROM, verified on load";
const char help_13[] PROGMEM = "skip     - set the position of a joint to 0, skipping it on moves";
const char help_14[] PROGMEM = "volt     - return the voltage of the battery";
const char help_15[] PROGMEM = "beep     - cause the arm to beep";
const char *const help_table[] PROGMEM =
    {
        help_0,
        help_1,
        help_2,
        help_3,
        help_4,
        help_5,
        help_6,
        help_7,
        help_8,
        help_9,
        help_10,
        help_11,
        help_12,
        help_13,
        help_14,
        help_15};

char volt_string[4] = {};
uint8_t volt_len = sizeof(volt_string) / sizeof(volt_string[0]);
char pos_string[4] = {};
uint8_t pos_len = sizeof(pos_string) / sizeof(pos_string[0]);
char temp_string[4] = {};
uint8_t temp_len = sizeof(temp_string) / sizeof(temp_string[0]);
char cmd_string[2] = {};

struct joint
{                // index serves as joint to move (1-6)
    int16_t pos; // position to move to (1-999)
    int16_t dur; // duration of move (0-3000)
    bool wait;   // whether or not to wait until move complete
};
struct joint vectors[N_joints][N_vectors];
#define EEPROM 0x0100
uint16_t eeprom_addr;
uint16_t vector_addr;

char *tokens[MAX_TOKENS];
int8_t g_joint = 1;
int16_t g_position;
int8_t g_vect_num = 0;
int8_t pos_size = 3;
int8_t joint_size = 7;

void init_xArm()
{
    soft_char_NL();
    soft_pgmtext_write(title);
    soft_char_NL();
}

void print_help()
{
    soft_char_NL();

    for (uint8_t i = 0; i < N_COMMANDS; i++)
    {
        soft_pgmtext_write(pgm_read_ptr(&(help_table[i])));
        soft_char_NL();
    }
    return;
}

uint8_t lowByte(uint16_t value)
{
    return (uint8_t)(value & 0xFF);
}

uint8_t highByte(uint16_t value)
{
    return (uint8_t)((value >> 8) & 0xFF);
}

int16_t xArm_clamp(int16_t v)
{
    return (v < xArm_lo) ? xArm_lo : (xArm_hi < v) ? xArm_hi
                                                   : v;
}

int8_t valid_joint(char *jnt)
{
    g_joint = atoi(jnt);
    if ((g_joint < 1) || (g_joint > 6))
    {
        soft_char_write(g_joint + ASCII_INTEGER);
        soft_char_BL();
        soft_pgmtext_write(hdr_cmd_badjoint);
        soft_char_write(N_joints + ASCII_INTEGER);
        soft_char_NL();
        return -1;
    }
    return 0;
}

int16_t valid_position(char *c_position)
{
    g_position = atoi(c_position);
    if ((g_position < 1) || (g_position > 999))
    {
        soft_string_write(tokens[t_pos], strlen(tokens[t_pos]));
        soft_char_BL();
        soft_pgmtext_write(hdr_cmd_badposition);
        soft_char_NL();
        return -1;
    }
    return 0;
}

int8_t valid_vector(char *vect)
{
    uint8_t v = (int)strtol(vect, (char **)NULL, 10);
    if ((v < 0) || (v >= N_vectors))
    {
        v = 0;
        soft_pgmtext_write(hdr_cmd_badvect);
        soft_char_write(N_vectors + ASCII_INTEGER - 1);
        soft_pgmtext_write(hdr_cmd_vect_0);
        soft_char_NL();
        return -1;
    }
    return v;
}

void vector_prompt()
{
    int8_t vector_char = g_vect_num + ASCII_INTEGER;
    soft_char_write(0x76);
    soft_char_write(vector_char);
    soft_char_write(0x3a);
    soft_char_BL();
}

void echo_command(uint8_t n)
{
    soft_pgmtext_write(hdr_cmd_rcd);
    for (uint8_t i = 0; i <= n; i++)
    {
        soft_string_write(tokens[i], strlen(tokens[i]));
        soft_char_BL();
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

    // xArm error reported
    case xArm:
        soft_pgmtext_write(hdr_cmd_xArm);
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
        soft_char_write(e + ASCII_INTEGER);
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
        if (xArm_in[0] == SIGNATURE && xArm_in[1] == SIGNATURE && xArm_in[3] == cmd)
        {
            int len = xArm_in[2] - 2;
            return readLine(xArm_in, len);
        }
    }
    return -1;
}

void xArm_beep()
{
    xArm_send(CMD_BEEP, 1);
}

int8_t valid_move(char *j, char *p)
{
    int8_t r;
    r = valid_joint(j);
    if (r == -1)
    {
        return r;
    }
    r = valid_position(p);
    if (r == -1)
    {
        return r;
    }
    xArm_setPosition(g_joint, g_position);
    return 0;
}

int8_t valid_add(char *j, char *p)
{
    int8_t r;
    r = valid_joint(j);
    if (r == -1)
    {
        return r;
    }
    r = valid_position(p);
    if (r == -1)
    {
        return r;
    }

    add_position();
    return 0;
}

int8_t valid_skip(char *j)
{
    int8_t r;
    r = valid_joint(j);
    if (r == -1)
    {
        return r;
    }
    g_position = 0;
    add_position();
    return 0;
}

uint8_t show_adds()
{
    for (int8_t i = 1; i <= N_joints; i++)
    {
        soft_pgmtext_write(hdr_cmd_move);
        show_joint_pos(i, g_vect_num);
        soft_char_NL();
    }
    return 0;
}

uint8_t show_vecs()
{
    for (int8_t i = 0; i < N_vectors; i++)
    {
        soft_pgmtext_write(hdr_cmd_v_col);
        soft_char_write(i + ASCII_INTEGER);
        for (int8_t i = 0; i < joint_size + pos_size; i++)
        {
            soft_char_BL();
        }
    }
    soft_char_NL();
    for (int8_t j = 1; j <= N_joints; j++)
    {
        for (int8_t v = 0; v < N_vectors; v++)
        {
            soft_pgmtext_write(hdr_cmd_move);
            show_joint_pos(j, v);
            soft_char_BL();
            soft_char_BL();
        }
        soft_char_NL();
    }
    return 0;
}

void show_joint_pos(int8_t j, int8_t v)
{
    soft_char_write(j + ASCII_INTEGER);
    soft_char_BL();
    int8_t j_index = j - 1;
    soft_int16_writef(vectors[j_index][v].pos, pos_size);
    return;
}
uint8_t exec_adds()
{
    for (uint8_t i = 1; i <= N_joints; i++)
    {
        if (vectors[i - 1][g_vect_num].pos == 0)
        {
            soft_pgmtext_write(hdr_cmd_skipped);
        }
        else
        {
            xArm_setPosition(i, vectors[i - 1][g_vect_num].pos);
            soft_pgmtext_write(hdr_cmd_move);
        }
        show_joint_pos(i, g_vect_num);
        soft_char_NL();
    }
    return 0;
}

uint8_t reset_adds()
{
    for (int8_t i = 0; i < N_joints; i++)
    {
        vectors[i][g_vect_num].pos = 0;
        vectors[i][g_vect_num].dur = 1000;
        vectors[i][g_vect_num].wait = true;
    }
    return 0;
}

void add_position()
{
    uint16_t duration = 1000;
    bool wait = true;

    int8_t i = g_joint - 1; // convert joint to joints index
    vectors[i][g_vect_num].pos = g_position;
    vectors[i][g_vect_num].dur = duration;
    vectors[i][g_vect_num].wait = wait;
    return;
}

void xArm_setPosition(uint8_t servo_id, int16_t position)
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
    if (wait)
    {
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
        for (int j = 1; j <= N_joints; j++)
        {
            eeprom_update_word((uint16_t *)(eeprom_addr), vectors[j - 1][v].pos);
            eeprom_addr += sizeof(int16_t);

            eeprom_update_word((uint16_t *)(eeprom_addr), vectors[j - 1][v].dur);
            eeprom_addr += sizeof(int16_t);

            eeprom_update_byte((uint8_t *)(eeprom_addr), vectors[j - 1][v].wait);
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
        for (int j = 1; j <= N_joints; j++)
        {
            vectors[j - 1][v].pos = eeprom_read_word((uint16_t *)(eeprom_addr));
            eeprom_addr += sizeof(int16_t);

            vectors[j - 1][v].dur = eeprom_read_word((uint16_t *)(eeprom_addr));
            eeprom_addr += sizeof(int16_t);

            vectors[j - 1][v].wait = eeprom_read_byte((uint8_t *)(eeprom_addr));
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
    for (int j = 1; j <= N_joints; j++)
    {
        p = eeprom_read_word((uint16_t *)(eeprom_addr));
        if (p != vectors[j - 1][v].pos)
        {
            verify = FALSE;
        }
        eeprom_addr += sizeof(int16_t);

        d = eeprom_read_word((uint16_t *)(eeprom_addr));
        if (d != vectors[j - 1][v].dur)
        {
            verify = FALSE;
        }
        eeprom_addr += sizeof(int16_t);

        w = eeprom_read_byte((uint8_t *)(eeprom_addr));
        if (w != vectors[j - 1][v].wait)
        {
            verify = FALSE;
        }
        eeprom_addr += sizeof(bool);
    }
    if (!verify)
    {
        soft_char_write(v + ASCII_INTEGER);
        soft_pgmtext_write(hdr_cmd_verify_error);
        soft_char_NL();
        return -1;
    }
    else
    {
        soft_pgmtext_write(hdr_verified);
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
    soft_pgmtext_write(hdr_volt);
    soft_int16_write(voltage);
    soft_char_NL();
    return 0;
}

uint16_t xArm_getBatteryVoltage()
{
    xArm_send(CMD_GET_BATTERY_VOLTAGE, 0);
    int8_t r = xArm_recv(CMD_GET_BATTERY_VOLTAGE);
    if (r != -1)
    {
        return (xArm_in[1] << 8) + xArm_in[0];
    }
    return r;
}

int8_t print_position(char *j)
{
    int8_t r = valid_joint(j);
    if (r == -1)
    {
        return badparms;
    }
    int16_t position = xArm_getPosition(g_joint);
    if (position == -1)
    {
        return badparms;
    }
    soft_char_write(*j);
    soft_char_BL();
    soft_pgmtext_write(hdr_pos);
    soft_int16_write(position);
    soft_char_NL();
    return 0;
}

int8_t get_vect_num(char *v)
{
    g_vect_num = valid_vector(v);
    if (g_vect_num == -1)
    {
        g_vect_num = 0;
        return badparms;
    }
    // soft_char_write(*v);
    // soft_char_BL();
    // soft_char_NL();
    return 0;
}

uint8_t show_all()
{
    for (uint8_t i = 1; i <= N_joints; i++)
    {
        char j_c = i + ASCII_INTEGER;
        print_position(&j_c);
    }
    return 0;
}

int8_t perf_all()
{
    for (uint8_t i = 0; i < N_vectors; i++)
    {
        g_vect_num = i;
        vector_prompt();
        soft_char_NL();
        exec_adds();
        delay(1000);
    }
    return 0;
}

uint16_t xArm_getPosition(uint8_t servo_id)
{
    xArm_out[0] = 1;
    xArm_out[1] = servo_id;
    xArm_send(CMD_GET_SERVO_POSITION, 2);
    int8_t r = xArm_recv(CMD_GET_SERVO_POSITION);
    if (r != -1)
    {
        return (xArm_in[3] << 8) + xArm_in[2];
    }
    return xArm;
}
