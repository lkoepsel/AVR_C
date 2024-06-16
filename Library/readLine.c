#include "readLine.h"

uint8_t readLine(char *buffer, uint8_t SIZE)
{
    uint8_t n_chars = 0;
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
            buffer[n_chars] = temp;
            n_chars++;
            if (n_chars >= SIZE)
            {
                EOL = 1;
            }
        }
    }
    while (!EOL);
    return n_chars;
}
