#include "flash.h"
#include <avr/io.h>
#include <util/delay.h>

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
    _delay_us(0.01); /* delay < tWP */

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
    _delay_us(0.01); /* delay < tWP */

    /* latch address */
    PORTB = address;
    PORTD |= ADDR_LATCH;
    PORTD |= WRITE_ENABLE;

    /* reset */
    PORTD &= ~ADDR_LATCH;
}


/* Get 'size' bytes of data from flash chip */
static void get_data(uint8_t *data, int size)
{
    set_data_input();
    for (int i = 0; i < size; i++)
    {
        /* maybe wait until ready? */
        PORTD &= ~READ_ENABLE;
        _delay_us(0.01);
        data[i] = PINB;
        PORTD |= READ_ENABLE;
    }
}


/* Wait for r/b# to be high */
static void wait_ready()
{
    while (!(PIND & READY_BUSY));
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

    wait_ready();
    /* issue reset command */
    command_cycle(0xFF);
    wait_ready();
}


/* Read chip code and return 5 bytes in id */
void flash_read_id(uint8_t *id)
{
    set_data_output();
    command_cycle(0x90);
    address_cycle(0x00);
    get_data(id, 5);
}


/* Read a single page from flash */
void flash_read_page(uint8_t *data)
{
    set_data_output();

    /* read page into cache */
    command_cycle(0x00);
    address_cycle(0x00);
    command_cycle(0x30);
    wait_ready();

    /* read from cache */
    for (int i = 0; i < 8; i++)
    {
        command_cycle(0x05);
        address_cycle(0x00);
        address_cycle(0x00);
        command_cycle(0xE0);
        _delay_us(1);
        get_data(data + i, 1);
    }
}

