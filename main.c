#include <8051.h>

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
    /* f = 20MHz
     * f_timer = 20MHz / 16 = 3.33MHz
     * baud = 115200
     * ticks = f_timer / baud = 29
     * TH1 = 0xFF - ticks = 226
     */
    TMOD = 0x20;    /* timer 1 in mode 2 (8-bit overflow) */
    TH1 = 0xF5;     /* timer reload value */
    PCON |= 0x80;

    /* uart */
    SCON = 0x50;     /* mode 1 (8 bit tx/rx) */

    TR1 = 1;
}


void main()
{
    /* setup UART */
    init_uart();
    P1 = 0x00;
    while(1)
    {
        P1 ^= 0x01;
        SBUF = 'a';

        while (TI == 0);
        TI = 0;

        delay();
    }   
}

