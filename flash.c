#include <8051.h>
#include "flash.h"

/* Initialize the chip to be disabled. */
void flash_init()
{
    CTRL_PORT |= OUTPUT_ENABLE | WRITE_ENABLE;
    CTRL_PORT &= ~CHIP_ENABLE;
}


/* Set address GPIO lines. */
void flash_set_address(address_t *address)
{
    /* set address for ports 1 and 2 */
    P1 = address->low;
    P2 = address->middle;

    /* clear port 3 bytes and set address */
    P3 &= ~(7 << 2);   /* clear 3.2, 3.3, 3.4 */
    char high_bits = address->high;
    high_bits &= 0x07; /* isolate first three bits */
    high_bits <<= 2;   /* shift bits over to match port */
    P3 |= high_bits;

    flash_delay(TIME_QUICK);
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
        flash_delay(TIME_QUICK);
        DATA_PORT = data[i];
        flash_delay(TIME_QUICK);
        CTRL_PORT |= WRITE_ENABLE;    /* latch data */
        flash_delay(TIME_QUICK);
    }
}


/* Write to flash */
void flash_program(char data, address_t *address)
{
    const char sdp_data[4] = { 0xAA, 0x55, 0xA0, data };
    const address_t sdp_addresses[4] = {
        { 0x00, 0x55, 0x55 },
        { 0x00, 0x2A, 0xAA },
        { 0x00, 0x55, 0x55 },
        { address->high, address->middle, address->low }
    };
    flash_sdp(sdp_addresses, sdp_data, 4);

    /* restore */
    flash_init();
}


/* Read from address */
char flash_read(address_t *address)
{
    flash_set_address(address);

    /* read */
    CTRL_PORT &= ~OUTPUT_ENABLE;
    char data = DATA_PORT;

    /* restore and return */
    flash_init();
    return data;
}


/* Erase bytes in a sector. Constrain address to multiple of 4kb */
void flash_erase(address_t *address)
{
    /* make address a multiple of 4k */
    address_t address_sector;
    address_sector.low = 0x00;
    address_sector.middle = address->middle & 0xF0;
    address_sector.high = address->high;

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


/* Delay some time: count = 0xFF is about 0.5 seconds */
void flash_delay(char count)
{
    for (char i = 0; i < 0xFF; i++)
    {
        for (char j = 0; j < count; j++);
    }
}


/* Get id of flash chip */
char flash_get_id()
{
    /* software id entry */
    static const char sdp_data[3] = {
        0xAA, 0x55, 0x90
    };
    const address_t sdp_addresses[3] = {
        { 0x00, 0x55, 0x55 },
        { 0x00, 0x2A, 0xAA },
        { 0x00, 0x55, 0x55 }
    };
    flash_sdp(sdp_addresses, sdp_data, 3);

    char id;
    address_t id_addr = { 0x00, 0x00, 0x01 };
    id = flash_read(&id_addr);

    /* restore */
    flash_init();

    return id;
}

