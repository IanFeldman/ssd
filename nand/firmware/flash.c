#include "flash.h"
#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>

static const uint8_t CHIP_ENABLE_TABLE_G[5] =
    { 0x00, CHIP_ENABLE_1, CHIP_ENABLE_2, CHIP_ENABLE_3, CHIP_ENABLE_4 };

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
    _delay_us(1); /* delay < tWP */

    /* latch command */
    PORTB = command;
    PORTD |= CMD_LATCH;
    PORTD |= WRITE_ENABLE;

    /* reset */
    PORTD &= ~CMD_LATCH;
    _delay_us(1); /* delay < tWP */
}


/* Perform single address output cycle */
static void address_cycle(uint8_t address)
{
    /* set write enable low */
    PORTD &= ~WRITE_ENABLE;
    _delay_us(1); /* delay < tWP */

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
    set_data_input();
    for (int i = 0; i < size; i++)
    {
        PORTD &= ~READ_ENABLE;
        _delay_us(1);
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
static void wait_ready(int chip)
{
    while (chip == 1 && !(PIND & READY_BUSY_1));
    while (chip == 2 && !(PIND & READY_BUSY_2));
    while (chip == 3 && !(PIND & READY_BUSY_3));
    while (chip == 4 && !(PINC & READY_BUSY_4));
}


/* Initialize pin connections */
void flash_init()
{
    /* set data pin directions */
    set_data_output();
    /* set enable pins as outputs */
    DDRC |= CHIP_ENABLE_DIR_1 | CHIP_ENABLE_DIR_2 | CHIP_ENABLE_DIR_3 | CHIP_ENABLE_DIR_4;
    /* set enable pin default value high */
    PORTC |= CHIP_ENABLE_1 | CHIP_ENABLE_2 | CHIP_ENABLE_3 | CHIP_ENABLE_4;
    /* set ready pins as inputs */
    DDRD &= ~(READY_BUSY_DIR_1 | READY_BUSY_DIR_2 | READY_BUSY_DIR_3);
    DDRC &= ~(READY_BUSY_DIR_4);
    /* set ready pins no pullup */
    PORTD &= ~(READY_BUSY_1 | READY_BUSY_2 | READY_BUSY_3);
    PORTC &= ~(READY_BUSY_4);
    /* set flash ctrl pins as outputs */
    DDRD |= ADDR_LATCH_DIR | CMD_LATCH_DIR | READ_ENABLE_DIR | WRITE_ENABLE_DIR | WRITE_PROT_DIR;
    /* set flash ctrl pints to default values */
    PORTD |= READ_ENABLE | WRITE_ENABLE | WRITE_PROT;
    PORTD &= ~(ADDR_LATCH | CMD_LATCH);
    uart_print_nl("Flash control pins initialized");

    /* reset all chips */
    uint8_t ce = 0x00;
    for (int i = 1; i <= CHIP_COUNT; i++)
    {
        ce = CHIP_ENABLE_TABLE_G[i];
        PORTC &= ~ce;
        wait_ready(i);
        command_cycle(RESET_CMD);
        wait_ready(i);
        PORTC |= ce;
        uart_print("Reset NAND chip ");
        uart_print_hex(i);
        uart_print_esc(NEW_LINE);
    }
}


/* Enable a chip */
void flash_enable(int chip)
{
    uint8_t ce = CHIP_ENABLE_TABLE_G[chip];
    PORTC &= ~ce;
}


/* Disable a chip */
void flash_disable(int chip)
{
    uint8_t ce = CHIP_ENABLE_TABLE_G[chip];
    PORTC |= ce;
}


/* Read chip code and return 5 bytes in id */
void flash_read_id(uint8_t *id, int chip)
{
    set_data_output();
    command_cycle(READ_ID_CMD);
    address_cycle(0x00);
    get_data(id, 5);
}


/* Read a single byte from flash */
uint8_t flash_read(uint32_t address, uint16_t column, int chip)
{
    set_data_output();

    /* read page into cache */
    command_cycle(READ_PAGE_CMD);
    latch_column(column);
    latch_address(address);
    command_cycle(END_READ_PAGE_CMD);
    wait_ready(chip);

    /* random read or start reading bytes */

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


/* Program data at address and column */
void flash_program(uint32_t address, uint16_t column,
    uint8_t *data, int size, int chip)
{
    set_data_output();

    /* load page into cache for programming */
    command_cycle(PROGRAM_PAGE_CMD);
    latch_column(column);
    latch_address(address);
    _delay_us(1); /* delay > tADL */

    /* random program, or start inputting bytes */
    set_data(data, size);

    /* done */
    command_cycle(END_PROGRAM_PAGE_CMD);
    wait_ready(chip);
}


/* Erase block of data at address */
void flash_erase(uint32_t address, int chip)
{
    set_data_output();
    command_cycle(ERASE_BLOCK_CMD);
    latch_address(address);
    command_cycle(END_ERASE_BLOCK_CMD);
    wait_ready(chip);
}

