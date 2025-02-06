#include "uart.h"

void delay()
{
    for (int i = 0; i < 0xFF; i++)
    {
        for (int j = 0; j < 0xFF; j++);
    }
}


void main()
{
    uart_init();
    uart_print_esc(CLEAR_SCREEN);
    uart_print_esc(HOME_CURSOR);

    while(1)
    {
        uart_print("Hello, world!");
        uart_print_esc(NEW_LINE);
        delay();
    }   
}

