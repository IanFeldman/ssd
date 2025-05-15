#include "flash.h"
#include "uart.h"

int main()
{
    /* configure uart */
    uart_init();
    uart_print_esc(CLEAR_SCREEN);
    uart_print_esc(HOME_CURSOR);
    uart_print_nl("UART initialized");

    /* configure flash */
    flash_init();
    uart_print_nl("Flash initialized");

    for (int chip = 1; chip <= 4; chip++)
    {
        uart_print_esc(NEW_LINE);
        uart_print("Testing chip: ");
        uart_print_hex(chip);
        uart_print_esc(NEW_LINE);

        flash_enable(chip);

        /* read id */
        uint8_t id[5] = {0, 0, 0, 0, 0};
        flash_read_id(id, chip);
        uart_print("Flash ID: ");
        for (int i = 0; i < 5; i++)
        {
            uart_print_hex(id[i]);
            uart_print(" ");
        }
        uart_print_esc(NEW_LINE);

        uint32_t address = 0x00000000;
        uint16_t column = 0x0000;

        /* read byte */
        uint8_t data = flash_read(address, column, chip);
        uart_print("Read data: ");
        uart_print_hex(data);
        uart_print_esc(NEW_LINE);

        /* erase byte */
        flash_erase(address, chip);
        uart_print_nl("Erased block");

        /* program byte */
        /*
        data = 0xAB;
        flash_program(0, 0, &data, sizeof(data), chip);
        uart_print("Wrote data: ");
        uart_print_hex(data);
        uart_print_esc(NEW_LINE);
        */

        /* reread byte */
        data = flash_read(address, column, chip);
        uart_print("Read data: ");
        uart_print_hex(data);
        uart_print_esc(NEW_LINE);

        flash_disable(chip);
    }
    return 0;
}

