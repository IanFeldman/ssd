// uart.c
#include "uart.h"
#include <util/delay.h>

// Volatile so the ISR can write to them 
volatile char input_ready = 0;    // Global flag indicating a complete line of input has been received
volatile char input[INPUT_MAX];   // Global buffer to store incoming characters

void UART0_init(void)
{	
    unsigned int ubrr_value = (F_CPU / (16UL * 38400)) - 1;  // For F_CPU = 8MHz, this evaluates to 12.
    UBRR0H = (unsigned char)(ubrr_value >> 8);                // Sets the high byte of the baud rate register to 0
    UBRR0L = (unsigned char)(ubrr_value & 0xFF);              // Sets the low byte of the baud rate register to 12
    UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);      // Enable transmitter, receiver, and RX complete interrupt  
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);                   // 8 data bits, 1 stop bit, no parity
}

void uart_print_char(char c)  // Transmit single character
{
    while (!(UCSR0A & (1 << UDRE0))) {  // Wait until the buffer is empty        
    }
    UDR0 = c;
}

void uart_print(const char *string)  // Prints a null-terminated string
{
    if (!string) {  // If string is null
        return;
    }
    while (*string) {
        uart_print_char(*string++);  // Sends each character via uart_print_char()
    }
}

void uart_print_esc(const char *code)  // Prints escape sequence
{
    if (!code) {  // If code is null
        return;
    }
    uart_print_char(ESC_CHAR);  // Prints 0x1B then code
    uart_print(code);
}

void uart_print_hex(uint8_t val)  // Prints hex conversion
{
    static const char hex_digits[] = "0123456789ABCDEF";  // Lookup string
    uart_print_char(hex_digits[val >> 4]);   // High nibble into hex
    uart_print_char(hex_digits[val & 0x0F]);   // Low nibble into hex
}

ISR(USART0_RX_vect)  // Interrupt service routine: runs whenever a new character arrives in UART0 data register
{
    static char input_index = 0;  // Tracks current position in input buffer
    char c = UDR0;                // Read incoming character

    if (c == RETURN_KEY || input_index >= (INPUT_MAX - 1)) {  // If enter is pressed or buffer is full
        input[input_index] = '\0';  // Null-terminate so input becomes a valid C-string
        input_ready = 1;            // Ready for input
        input_index = 0;            // Reset index
    } else {
        input[input_index++] = c;   // Store character
        uart_print_char(c);         // Echo back to user
    }
}

char uart_get_input_ready(void)  // Returns the current value of input_ready
{
    return input_ready;
}

void uart_reset_input_ready(void)  // Clears input_ready
{
    input_ready = 0;
}

char *uart_get_input(void)  // Gives pointer to the global input buffer so the main program can read the received string
{
    return (char *)input;
}

void uart_print_int(uint32_t value)
{
	char buffer[12];          // Buffer to hold up to 10 digits plus sign and null terminator
	ultoa(value, buffer, 10); // Convert unsigned long to string in base 10
	uart_print(buffer);       // Print the resulting string
}
