#ifndef UART_H
#define UART_H

#define ESC_CHAR 0x1b
#define NEW_LINE "[1E"
#define HOME_CURSOR "[H"
#define CLEAR_SCREEN "[2J"

#define INPUT_MAX 8
#define RETURN_KEY 0x0D

void uart_init();
void uart_print(char *string);
void uart_print_esc(char *code);
void uart_print_char(char ch);
void uart_print_hex(char val);

void uart_isr() __interrupt (4);
char uart_get_input_ready();
void uart_reset_input_ready();
char *uart_get_input();

#endif /* UART_H */

