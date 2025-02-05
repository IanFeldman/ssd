#include <8051.h>
#include <string.h>

void delay()
{
    for (int i = 0; i < 0xFF; i++)
    {
        for (int j = 0; j < 0xFF; j++);
    }
}


void init_uart()
{
    /* timer */
    TMOD |= 0x20;   /* timer 1 in mode 2 (8-bit overflow) */
    TH1   = 0xF5;   /* timer reload value for baud = 9600 */
    PCON |= 0x80;   /* set SMOD1 */
    TCON |= 0x40;   /* enable timer */

    /* uart */
    SCON  = 0x50;    /* mode 1 (8 bit tx/rx) */
}


void print(char *string)
{
    const char *str = string;
    if (!string)
    {
        str = "Error string is null";
    }
    for (int i = 0; i < strlen(str); i++)
    {
        SBUF = str[i];
        while (TI == 0);
        TI = 0;
    }
}


void main()
{
    init_uart();
    P1 = 0x00;
    while(1)
    {
        P1 ^= 0x01;
        print("Hello, world! ");
        delay();
    }   
}

