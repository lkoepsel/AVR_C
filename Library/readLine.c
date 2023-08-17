#include "readLine.h"

uint8_t readLine(char *buffer, uint8_t SIZE)
{
    uint8_t in_char = 0;
    uint8_t EOL = 0;
    do
    {
        char temp = getchar();
        if (temp == CR)
        {
            EOL = 1;
        }
        else
        {
            buffer[in_char] = temp;
            in_char++;
            if (in_char >= SIZE)
            {
                EOL = 1;
            }
        }
    }
    while (!EOL);
    return in_char;
}
