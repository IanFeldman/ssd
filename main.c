#include "flash.h"
#include "uart.h"

void parse_input(char *input)
{
    uart_print_esc(NEW_LINE);
    switch (input[0])
    {
        case 'r':
            uart_print("r");
            break;
        case 'p':
            uart_print("p");
            break;
        case 'e':
            uart_print("e");
            break;
        default:
            uart_print("?");
            uart_reset_input_ready();
            uart_print_esc(NEW_LINE);
            uart_print("> ");
            return;
    }
    uart_reset_input_ready();
}


void main()
{
    /* initialize peripherals */
    uart_init();
    flash_init();

    /* reset screen */
    uart_print_esc(CLEAR_SCREEN);
    uart_print_esc(HOME_CURSOR);
    uart_print("> ");

    while(1)
    {
        /* check if input is ready */
        if (uart_get_input_ready())
        {
            parse_input(uart_get_input());
        }
    }
}

