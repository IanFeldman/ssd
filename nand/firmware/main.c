#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "flash.h"
#include "uart.h"

int main()
{
    /* configure uart */
    uart_init();
    uart_print_esc(CLEAR_SCREEN);
    uart_print_esc(HOME_CURSOR);
    uart_print("UART initialized");
    uart_print_esc(NEW_LINE);

    /* configure flash */
    flash_init();
    uart_print("Flash initialized");
    uart_print_esc(NEW_LINE);

    return 0;
}

