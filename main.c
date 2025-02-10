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
    uart_print("Starting");
    uart_print_esc(NEW_LINE);
    flash_delay(0xFF);

    address_t addr = { 0x00, 0x00, 0xAB };
    flash_erase(&addr);
    flash_program(0xBF, &addr);

    flash_delay(0xFF);

    char data = flash_read(&addr);
    uart_print("read: 0x");
    uart_print_hex(data);
    uart_print_esc(NEW_LINE);

    while(1);
}

