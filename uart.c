#include <8051.h>
#include "uart.h"

volatile char input_ready;
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

    /* interrupts */
    EA = 1;
    ES = 1;
}


/* Print string over serial. */
void uart_print(char *string)
{
    /* check if string is null */
    if (!string)
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
    if (!code)
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


/* Print address as hex */
void uart_print_addr(address_t *addr)
{
    uart_print_hex(addr->high);
    uart_print_hex(addr->middle);
    uart_print_hex(addr->low);
}


/* Interrupt that receives serial data */
void uart_isr() __interrupt (4)
{
    static char input_index = 0;

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
    /* clear input bufffer */
    for (char i = 0; i < INPUT_MAX; i++)
    {
        input[i] = 0;
    }
}


/* Get input buffer */
char *uart_get_input()
{
    return input;
}


/* Convert 2 byte hex string to char */
char uart_hex_to_char(char *val)
{
    char result = 0;
    char place = 16;

    for (char i = 0; i < 2; i++)
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
        place = 1;
    }

    return result;
}


/* Convert 6 byte hex string to address */
void uart_hex_to_addr(char *val, address_t *addr)
{
    addr->high = uart_hex_to_char(val);
    addr->middle = uart_hex_to_char(val + 2);
    addr->low = uart_hex_to_char(val + 4);
}

