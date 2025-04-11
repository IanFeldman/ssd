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

    /* read byte */
    uint8_t data = flash_read(0, 0);
    uart_print("Read data: ");
    uart_print_hex(data);
    uart_print_esc(NEW_LINE);

    /* program byte */
    data = 0xAB;
    flash_program(0, 0, &data, sizeof(data));
    uart_print("Wrote data: ");
    uart_print_hex(data);
    uart_print_esc(NEW_LINE);

    /* reread byte */
    data = flash_read(0, 0);
    uart_print("Read data: ");
    uart_print_hex(data);
    uart_print_esc(NEW_LINE);

    return 0;
}

