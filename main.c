#include "flash.h"
#include "uart.h"

void main()
{
    uart_init();
    uart_print_esc(CLEAR_SCREEN);
    uart_print_esc(HOME_CURSOR);

    flash_init();

    flash_delay();

    address_t addr = { 0x00, 0x00, 0x00 };
    char data = flash_read(&addr);
    uart_print("Read: 0x");
    uart_print_hex(data);
    uart_print_esc(NEW_LINE);

    while(1)
    {
        uart_print("running...");
        uart_print_esc(NEW_LINE);
        flash_delay();
    }   
}

