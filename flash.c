#include <8051.h>
#include "flash.h"

/* Initialize the chip to be disabled. */
void flash_init()
{
    CTRL_PORT |= OUTPUT_ENABLE | WRITE_ENABLE;
    CTRL_PORT &= ~CHIP_ENABLE;

    /* configure data port as input */
    DATA_PORT = 0xFF;
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


/* Write software data protection bytes
 * addresses: list of addresses in order
 * data: list of data in order
 * count: number of bytes to program
 */
void flash_sdp(address_t *addresses, char *data, char count)
{
    for (char i = 0; i < count; i++)
    {
        flash_set_address(&addresses[i]);
        CTRL_PORT &= ~WRITE_ENABLE;    /* latch address */
        DATA_PORT = data[i];
        CTRL_PORT |= WRITE_ENABLE;    /* latch data */
        flash_delay(TIME_QUICK);      /* small delay */
    }
}


/* Write to flash */
void flash_program(char data, address_t *address)
{
    /* enable chip */
    CTRL_PORT &= ~CHIP_ENABLE;
    flash_delay(TIME_QUICK);

    static const char sdp_data[3] = { 0xAA, 0x55, 0xA0 };
    static const address_t sdp_addresses[3] = {
        { 0x00, 0x55, 0x55 },
        { 0x00, 0x2A, 0xAA },
        { 0x00, 0x55, 0x55 }
    };
    flash_sdp(sdp_addresses, sdp_data, 3);

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
    flash_delay(TIME_QUICK);
    char data = DATA_PORT;

    /* restore and return */
    flash_init();
    return data;
}


/* Clear bytes */
void flash_erase(address_t *address)
{
    /* enable chip */
    CTRL_PORT &= ~CHIP_ENABLE;
    flash_delay(TIME_QUICK);

    static const char sdp_data[6] = {
        0xAA, 0x55, 0x80, 0xAA, 0x55, 0x30
    };
    const address_t sdp_addresses[6] = {
        { 0x00, 0x55, 0x55 },
        { 0x00, 0x2A, 0xAA },
        { 0x00, 0x55, 0x55 },
        { 0x00, 0x55, 0x55 },
        { 0x00, 0x2A, 0xAA },
        { address->high, address->middle, address->low }
    };
    flash_sdp(sdp_addresses, sdp_data, 6);

    /* restore */
    flash_init();
}


/* Delay about half a second */
void flash_delay(char count)
{
    for (char i = 0; i < 0xFF; i++)
    {
        for (char j = 0; j < count; j++);
    }
}

