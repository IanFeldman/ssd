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


/* Print string with new line appended. */
void uart_print_ln(char *string)
{
    uart_print(string);
    uart_print_esc(NEW_LINE);
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
void uart_print_hex(uint8_t val)
{
    uart_print_char("0123456789ABCDEF"[val >> 4]);
    uart_print_char("0123456789ABCDEF"[val & 0x0F]);
}


/* Print address as hex */
void uart_print_address(uint32_t row, uint16_t col)
{
    uart_print("row: 0x");
    uart_print_hex(row >> 24);
    uart_print_hex(row >> 16);
    uart_print_hex(row >> 8);
    uart_print_hex(row >> 0);

    uart_print(", column: 0x");
    uart_print_hex(col >> 8);
    uart_print_hex(col >> 0);
    uart_print_esc(NEW_LINE);
}

