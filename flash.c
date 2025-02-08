#include <8051.h>
#include "flash.h"

/* Initialize the chip to be disabled. */
void flash_init()
{
    CTRL_PORT |= CHIP_ENABLE | OUTPUT_ENABLE | WRITE_ENABLE;
}


/* Set address GPIO lines. */
void flash_set_address(address_t *address)
{
    /* set address for ports 1 and 2 */
    P1 = address->low;
    P2 = address->middle;

    /* clear port 3 bytes */
    char high_bits = address->high;
    P3 &= ~(7 << 2);
    high_bits &= 0x03; /* isolate first three bits */
    high_bits <<= 2;   /* shift bits over to match port */
    P3 |= high_bits;
}


/* Write to flash */
void flash_program(char data, address_t *address)
{
    /* enable chip */
    CTRL_PORT &= ~CHIP_ENABLE;
    flash_delay(TIME_QUICK);

    /* three byte sequence for software data protection */
    static address_t sdp_addr1 = { 0x00, 0x55, 0x55 };
    static address_t sdp_addr2 = { 0x00, 0x2A, 0xAA };
    static address_t sdp_addr3 = { 0x00, 0x55, 0x55 };

    flash_set_address(&sdp_addr1);
    CTRL_PORT &= ~WRITE_ENABLE;    /* latch address */
    DATA_PORT = 0xAA;
    CTRL_PORT |= WRITE_ENABLE;    /* latch data */
    flash_delay(TIME_QUICK);

    flash_set_address(&sdp_addr2);
    CTRL_PORT &= ~WRITE_ENABLE;
    DATA_PORT = 0x55;
    CTRL_PORT |= WRITE_ENABLE;
    flash_delay(TIME_QUICK);

    flash_set_address(&sdp_addr3);
    CTRL_PORT &= ~WRITE_ENABLE;
    DATA_PORT = 0xA0;
    CTRL_PORT |= WRITE_ENABLE;
    flash_delay(TIME_QUICK);

    /* begin programming */
    flash_set_address(address);
    CTRL_PORT &= ~WRITE_ENABLE;
    DATA_PORT = data;
    CTRL_PORT |= WRITE_ENABLE;

    /* wait at least 20us */
    flash_delay(TIME_QUICK);

    /* restore */
    flash_init();
}


/* Read from address */
char flash_read(address_t *address)
{
    flash_set_address(address);

    /* read */
    CTRL_PORT &= ~(CHIP_ENABLE | OUTPUT_ENABLE);
    char data = DATA_PORT;

    /* restore and return */
    flash_init();
    return data;
}


/* Clear bytes */
void flash_erase(address_t *addr)
{
    flash_set_address(addr);

    CTRL_PORT &= ~(CHIP_ENABLE | WRITE_ENABLE);
}


/* Delay about half a second */
void flash_delay(char count)
{
    for (char i = 0; i < 0xFF; i++)
    {
        for (char j = 0; j < count; j++);
    }
}

