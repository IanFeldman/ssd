// main.c
#include "nor.h"
#include "uart.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <avr/interrupt.h>

#define PROMPT "> "

#ifndef NEW_LINE
#define NEW_LINE "\r\n"
#endif

#ifndef CLEAR_SCREEN
#define CLEAR_SCREEN "[2J"
#endif


// Convert a 32-bit number into address_t (19 bits used).
// low    = bits 0–7
// middle = bits 8–15
// high   = bits 16–18

void dec_to_addr(uint32_t dec, address_t *addr)
{
    addr->low    = dec & 0xFF;
    addr->middle = (dec >> 8) & 0xFF;
    addr->high   = (dec >> 16) & 0x07;
}

// Print a flash address in decimal form by recombining
// the address_t fields into a 32-bit number.

void print_addr(const address_t *addr)
{
    uint32_t full_addr = ((uint32_t)(addr->high & 0x07) << 16)
                       | ((uint32_t)addr->middle << 8)
                       | (uint32_t)addr->low;
    uart_print_int(full_addr); // Now prints as 32-bit unsigned
}


// Expected commands (in hex):
// r <address>
// p <address> <data>
// e <address>

void parse_input(char *input)
{
    // Tokenize by spaces
    char *cmd = strtok(input, " ");
    if (cmd == NULL || strlen(cmd) == 0)
    {
        uart_print("Error: Empty command");
        uart_print_esc(NEW_LINE);
        uart_print(PROMPT);
        uart_reset_input_ready();
        return;
    }
    
    uart_print_esc(NEW_LINE);
    uart_print("\x1B[K");
    
    char command = cmd[0];
    uint32_t addr_val = 0;
    uint32_t data_val = 0;
    address_t addr;

    switch (command)
    {
        case 'r':  // read
        {
            char *addr_str = strtok(NULL, " ");
            if (!addr_str)
            {
                uart_print("Error: Missing address");
                break;
            }
            addr_val = (uint32_t)strtol(addr_str, NULL, 16);
            dec_to_addr(addr_val, &addr);
            {
                char value = flash_read(&addr);
                uart_print("Read byte 0x");
                uart_print_hex((uint8_t)value);
                uart_print(" from address ");
                print_addr(&addr);
            }
            break;
        }
        case 'p':  // program
        {
            char *addr_str = strtok(NULL, " ");
            char *data_str = strtok(NULL, " ");
            if (!addr_str || !data_str)
            {
                uart_print("Error: Missing address or data");
                break;
            }
            addr_val = (uint32_t)strtol(addr_str, NULL, 16);
            data_val = (uint32_t)strtol(data_str, NULL, 16);
            dec_to_addr(addr_val, &addr);
            flash_program((char)data_val, &addr);
            uart_print("Wrote byte 0x");
            uart_print_hex((uint8_t)data_val);
            uart_print(" to address ");
            print_addr(&addr);
            break;
        }
        case 'e':  // erase
        {
            char *addr_str = strtok(NULL, " ");
            if (!addr_str)
            {
                uart_print("Error: Missing address");
                break;
            }
            addr_val = (uint32_t)strtol(addr_str, NULL, 16);
            dec_to_addr(addr_val, &addr);
            flash_erase(&addr);
            uart_print("Erased sector starting at address ");
            print_addr(&addr);
            break;
        }
        default:
            uart_print("Unknown command");
    }
    uart_print_esc(NEW_LINE);
    uart_print(PROMPT);
    uart_reset_input_ready();
}

int main(void)
{
    UART0_init();
    flash_init();
    sei(); // enable global interrupts for UART

    uart_print_esc(CLEAR_SCREEN);
    uart_print(PROMPT);

    while (1)
    {
        if (uart_get_input_ready())
        {
            parse_input(uart_get_input());
        }
    }
    return 0;
}
