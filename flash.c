#include <8051.h>
#include "flash.h"

/* Initialize the chip to be disabled. */
void flash_init()
{
    P3 |= CHIP_ENABLE | OUTPUT_ENABLE | WRITE_ENABLE;
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


/* Write to flash. */
void flash_program(char data, address_t *address)
{
    /* latch address */
    flash_set_address(address);
    P3 &= ~(CHIP_ENABLE | OUTPUT_ENABLE);

    /* latch data */
    DATA_PORT = data;
    P3 |= WRITE_ENABLE;

    /* wait at least 20us */
    flash_delay();

    /* restore */
    flash_init();
}


/* Read from address. */
char flash_read(address_t *address)
{
    flash_set_address(address);

    /* read */
    P3 &= ~(CHIP_ENABLE | OUTPUT_ENABLE);
    char data = DATA_PORT;

    /* restore and return */
    flash_init();
    return data;
}


/* Clear bytes. */
void flash_erase()
{
}


/* Delay about half a second */
void flash_delay()
{
    for (char i = 0; i < 0xFF; i++)
    {
        for (char j = 0; j < 0xFF; j++);
    }
}

