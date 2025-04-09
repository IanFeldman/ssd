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

    /* read id */
    uint8_t id[5] = {0, 0, 0, 0, 0};
    flash_read_id(id);
    uart_print("Flash ID: ");
    for (int i = 0; i < 5; i++)
    {
        uart_print_hex(id[i]);
        uart_print(" ");
    }
    uart_print_esc(NEW_LINE);

    /* read page */
    int size = 8;
    uint8_t data[size];
    flash_read_page(data);
    uart_print("Data: ");
    for (int i = 0; i < size; i++)
    {
        uart_print_hex(data[i]);
        uart_print(" ");
    }
    uart_print_esc(NEW_LINE);

    return 0;
}

