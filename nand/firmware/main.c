#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

int main()
{
    /* configure uart */
    uart_init();
    uart_print_esc(CLEAR_SCREEN);
    uart_print_esc(HOME_CURSOR);

    /* set pin as output */
    DDRB |= (1 << PB0);

    while (1)
    {
        PORTB |= (1 << PB0);
        _delay_ms(250);
        uart_print("Hello, world.");
        uart_print_esc(NEW_LINE);

        PORTB &= ~(1 << PB0);
        _delay_ms(250);
    }

    return 0;
}

