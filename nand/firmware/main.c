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

        /* set address */
        uint32_t row = 0x00000028;
        uint16_t column = 0x0013;
        uart_print("At address ");
        uart_print_address(row, column);

        /* read byte */
        uint8_t data = flash_read(row, column, chip);
        uart_print("Read data: ");
        uart_print_hex(data);
        uart_print_esc(NEW_LINE);

        /* erase byte */
        flash_erase(row, chip);
        uart_print_nl("Erased block");

        /* reread byte */
        data = flash_read(row, column, chip);
        uart_print("Read data: ");
        uart_print_hex(data);
        uart_print_esc(NEW_LINE);

        /* program byte */
        data = 0xB6;
        flash_program(row, column, &data, sizeof(data), chip);
        uart_print("Wrote data: ");
        uart_print_hex(data);
        uart_print_esc(NEW_LINE);

        /* reread byte */
        data = flash_read(row, column, chip);
        uart_print("Read data: ");
        uart_print_hex(data);
        uart_print_esc(NEW_LINE);

        flash_disable(chip);
    }
    return 0;
}

