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


/* Perform single command output cycle */
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


/* Perform single address output cycle */
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


/* Perform output cycle for a 2-byte column */
static void latch_column(uint16_t column)
{
    uint8_t c1 = column & 0xFF;
    uint8_t c2 = (column >> 8) & 0xFF;
    address_cycle(c1);
    address_cycle(c2);
}


/* Perform output cycle for a 3-byte address */
static void latch_address(uint32_t address)
{
    uint8_t r1 = address & 0xFF;
    uint8_t r2 = (address >> 8) & 0xFF;
    uint8_t r3 = (address >> 16) & 0xFF;
    address_cycle(r1);
    address_cycle(r2);
    address_cycle(r3);
}


/* Get 'size' bytes of data from flash chip */
static void get_data(uint8_t *data, int size)
{
    for (int i = 0; i < size; i++)
    {
        PORTD &= ~READ_ENABLE;
        _delay_us(0.01);
        data[i] = PINB;
        PORTD |= READ_ENABLE;
    }
}


/* Set output data pins */
static void set_data(uint8_t *data, int size)
{
    for (int i = 0; i < size; i++)
    {
        PORTD &= ~WRITE_ENABLE;
        _delay_us(0.01);
        PINB = data[i];
        PORTD |= WRITE_ENABLE;
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
    command_cycle(READ_ID_CMD);
    address_cycle(0x00);
    get_data(id, 5);
}


/* Read a single byte from flash */
uint8_t flash_read(uint32_t address, uint16_t column)
{
    set_data_output();

    /* read page into cache */
    command_cycle(READ_PAGE_CMD);
    latch_column(column);
    latch_address(address);
    command_cycle(END_READ_PAGE_CMD);
    wait_ready();

    /* random read or start reading bytes */

    set_data_input();
    /* read first byte */
    uint8_t data;
    get_data(&data, 1);
    return data;

    /* random read */
    /*
    command_cycle(RANDOM_READ_CMD);
    latch_column(somewhere);
    command_cycle(END_RANDOM_READ_CMD);
    wait_ready();
    get_data(&data, 1);
    return data;
    */
}


void flash_program(uint32_t address, uint16_t column,
    uint8_t *data, int size)
{
    set_data_output();

    /* load page into cache for programming */
    command_cycle(PROGRAM_PAGE_CMD);
    latch_column(column);
    latch_address(address);
    _delay_us(0.1); /* delay > tADL */

    /* random program, or start inputting bytes */
    set_data(data, size);

    /* done */
    command_cycle(END_PROGRAM_PAGE_CMD);
    wait_ready();
}

