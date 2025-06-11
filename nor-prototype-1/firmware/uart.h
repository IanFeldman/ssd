// uart.h
#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <avr/interrupt.h>

// CPU frequency (8 MHz); make sure your fuses or external clock match this
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

// Desired baud rate
#define BAUD_RATE 38400

// Input buffer settings
#define INPUT_MAX   128
#define RETURN_KEY  '\r'  // Tera Term often sends '\r' on Enter
#define ESC_CHAR    0x1B  // ANSI escape character

void UART0_init(void);
void uart_print(const char *string);
void uart_print_char(char c);
void uart_print_esc(const char *code);
void uart_print_hex(uint8_t val);
char uart_get_input_ready(void);
void uart_reset_input_ready(void);
char *uart_get_input(void);
void uart_print_int(uint32_t value);

#endif

