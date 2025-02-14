#include <string.h>
#include <8051.h>
#include "uart.h"

/* Initialize uart peripheral, using timer 1 to generate baud. */
void uart_init()
{
    /* timer */
    TMOD |= 0x20;   /* timer 1 in mode 2 (8-bit overflow) */
    TH1   = 0xF5;   /* timer reload value for baud = 9600 */
    PCON |= 0x80;   /* set SMOD1 */
    TCON |= 0x40;   /* enable timer */

    /* uart */
    SCON  = 0x50;   /* mode 1 (8 bit tx/rx) + enable receive */

    /* interrupts */
    EA = 1;
    ES = 1;
}


/* Print string over serial. */
void uart_print(char *string)
{
    /* check if string is null */
    if (string == NULL)
    {
        return;
    }

    while (*string)
    {
        uart_print_char(*string++);
    }
}


/* Print an ANSI escape code over serial. */
void uart_print_esc(char *code)
{
    if (code == NULL)
    {
        return;
    }
    uart_print_char(ESC_CHAR);
    uart_print(code);
}


/* Print a single character over serial */
void uart_print_char(char ch)
{
    SBUF = ch;
    while (TI == 0);
    TI = 0;
}


/* Print value as hex */
void uart_print_hex(char val)
{
    uart_print_char("0123456789ABCDEF"[val >> 4]);
    uart_print_char("0123456789ABCDEF"[val & 0x0F]);
}


/* Interrupt that receives serial data */
void uart_isr() __interrupt (4)
{
    if (RI)
    {
        RI = 0;
        uart_print_char(SBUF);
    }
}

