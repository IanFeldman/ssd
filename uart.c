#include <string.h>
#include <8051.h>
#include "uart.h"

volatile char input_ready, input_index;
volatile char input[INPUT_MAX];

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

    input_ready = 0;
    input_index = 0;

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
    if (RI && !input_ready)
    {
        /* clear interrupt flag */
        RI = 0;

        /* parse input on enter */
        char c = SBUF;
        if (c == RETURN_KEY || input_index >= INPUT_MAX)
        {
            input_ready = 1;
            input_index = 0;
            return;
        }

        /* print input and add it to buffer */
        uart_print_char(c);
        input[input_index++] = c;
    }
}


/* Get input_ready flag */
char uart_get_input_ready()
{
    return input_ready;
}


/* Clear input ready flag */
void uart_reset_input_ready()
{
    input_ready = 0x00;
}


/* Get input buffer */
char *uart_get_input()
{
    return input;
}


/* Get length used of input buffer */
char uart_get_input_length()
{
    return input_index;
}

