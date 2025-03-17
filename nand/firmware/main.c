#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

int main()
{
    uart_init();
    DDRB |= (1 << PB0);

    while (1)
    {
        PORTB |= (1 << PB0);
        _delay_ms(250);
        uart_print("test");

        PORTB &= ~(1 << PB0);
        _delay_ms(250);
    }

    return 0;
}

