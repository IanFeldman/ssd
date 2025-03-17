#include <avr/io.h>
#include "uart.h"

/* Initialize uart peripheral. */
void uart_init()
{
    /* ubrr = clock / (16 * baud) - 1 */
    uint16_t ubrr = 103;
    /* Set baud rate */
    UBRR1H = (uint8_t)(ubrr >> 8);
    UBRR1L = (uint8_t)(ubrr);
    /* enable transmitter */
    UCSR1B = (1 << TXEN1);
    /* no parity, two stop bits, 8-bit data */
    UCSR1C = (1 << USBS1) | (3 << UCSZ10);
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
    /* wait for empty transmit buffer */
    while (!(UCSR1A & (1 << UDRE1)));
    /* put data in buffer */
    UDR1 = ch;
}


/* Print value as hex */
void uart_print_hex(char val)
{
    uart_print_char("0123456789ABCDEF"[val >> 4]);
    uart_print_char("0123456789ABCDEF"[val & 0x0F]);
}

