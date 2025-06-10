#include <stdint.h>
#include "util.h"

/* Convert hex string to integer (up to 32-bit) */
uint32_t hex_str_to_int(char *val, int len)
{
    int result = 0;
    int place = 16 ^ (len - 1);

    for (int i = 0; i < 4; i++)
    {
        char c = val[i];
        if (c >= '0' && c <= '9')
        {
            result += (c - '0') * place;
        }
        else if (c >= 'A' && c <= 'F')
        {
            result += (c - 'A' + 10) * place;
        }
        else
        {
            return 0;
        }
        place >>= 4; /* divide by 16 */
    }

    return result;
}

