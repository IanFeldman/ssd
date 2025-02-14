#include "flash.h"
#include "uart.h"

void main()
{
    /* initialize peripherals */
    uart_init();
    flash_init();

    /* reset screen */
    uart_print_esc(CLEAR_SCREEN);
    uart_print_esc(HOME_CURSOR);

    address_t addr = { 0x00, 0x00, 0x12 };
    flash_erase(&addr);
    flash_program(0x77, &addr);

    char data = flash_read(&addr);
    uart_print("read: 0x");
    uart_print_hex(data);
    uart_print_esc(NEW_LINE);

    while(1);
}

