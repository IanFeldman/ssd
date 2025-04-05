#include "flash.h"
#include <avr/io.h>

/* Set data lines as inputs */
static void set_data_input()
{
    /* port B: input without pulldowns */
    DDRB = 0x00;
    PORTB = 0x00;
}


/* Set data lines as outputs */
static void set_data_output()
{
    /* port B: output default 0 */
    DDRB = 0xFF;
    PORTB = 0x00;
}


/* Perform single command cycle */
static void command_cycle(uint8_t command)
{
    /* set write enable low */
    PORTD &= ~WRITE_ENABLE;

    /* latch command */
    PORTB = command;
    PORTD |= CMD_LATCH;
    PORTD |= WRITE_ENABLE;

    /* reset */
    PORTD &= ~CMD_LATCH;
}


/* Perform single address cycle */
static void address_cycle(uint8_t address)
{
    /* set write enable low */
    PORTD &= ~WRITE_ENABLE;

    /* latch address */
    PORTB = address;
    PORTD |= ADDR_LATCH;
    PORTD |= WRITE_ENABLE;

    /* reset */
    PORTD &= ~ADDR_LATCH;
}


/* Initialize pin connections */
void flash_init()
{
    /* set pin directions */
    set_data_output();
    /* chip enables in port C are output */
    DDRC = (1 << DDC2);
    /* all of port D is output except for r/b */
    DDRD = 0xFF & ~(1 << DDC7);
    /* set active low pins high by default */
    PORTD = READ_ENABLE | WRITE_ENABLE | WRITE_PROT;

    /* set chip enable high */
    PORTC &= ~CHIP_ENABLE;

    /* wait for r/b# to be high */
    while (!(PIND & READY_BUSY));
    /* issue reset command */
    command_cycle(0xFF);
    /* wait for complete */
    while (!(PIND & READY_BUSY));
}


void flash_read_id()
{
    command_cycle(0x90);
    address_cycle(0x00);
}

