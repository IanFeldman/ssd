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
    flash_delay(0xFF);

    /* create address */
    address_t addr = { 0x00, 0xB0, 0x20 };

    /* program */
    flash_program(0xAB, &addr);

    /* read */
    char data = flash_read(&addr);
    uart_print("Read: 0x");
    uart_print_hex(data);
    uart_print_esc(NEW_LINE);

    return;
}

