#ifndef UART_H
#define UART_H

#define ESC_CHAR 0x1b
#define NEW_LINE "[1E"
#define HOME_CURSOR "[H"
#define CLEAR_SCREEN "[2J"
#define RETREAT_CURSOR "[1D"

void uart_init(void);
void uart_print(char *string);
void uart_print_ln(char *string);
void uart_print_esc(char *code);
void uart_print_char(char ch);
void uart_print_hex(uint8_t val);
char uart_hex_to_char(char *val);
void uart_print_address(uint32_t row, uint16_t col);

#endif /* UART_H */

