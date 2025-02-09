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

    char id = flash_get_id();
    uart_print("Id: 0x");
    uart_print_hex(id);
    uart_print_esc(NEW_LINE);

    while(1) {}

    /*
    char data;
    for (char i = 0; i < 0xFF; i++)
    {
        address_t addr = { 0x00, 0x00, i };
        data = flash_read(&addr);
        uart_print("Read: 0x");
        uart_print_hex(data);
        uart_print_esc(NEW_LINE);
    }
    */
}

