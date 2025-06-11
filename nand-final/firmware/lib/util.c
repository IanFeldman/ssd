#include <stdint.h>
#include "util.h"

/* Convert hex string to integer (up to 32-bit) */
uint32_t hex_str_to_int(char *val, int len)
{
    uint32_t result = 0;

    for (int i = 0; i < len; i++)
    {
        char c = val[i + 2]; /* skip '0x' */
        uint8_t digit;

        if (c >= '0' && c <= '9')
        {
            digit = (c - '0');
        }
        else if (c >= 'A' && c <= 'F')
        {
            digit = (c - 'A' + 10);
        }
        else if (c >= 'a' && c <= 'f')
        {
            digit = (c - 'a' + 10);
        }
        else
        {
            return 0;
        }

        result = (result << 4) | digit;
    }

    return result;
}

/* Convert byte integeter to hex string.
 * String res must be of size 2
 */
void byte_to_hex_str(uint8_t val, char *res)
{
    res[0] = "0123456789ABCDEF"[val >> 4];
    res[1] = "0123456789ABCDEF"[val & 0x0F];
}

/* Return minimum of a and b */
unsigned int min(unsigned int a, unsigned int b)
{
    return (a < b) ? a : b;
}

