// nor.c

#include <avr/io.h>
#include "nor.h"

/*
 * Pin Mapping for ATmega1284 to SST39SF040:
 *   A0-A7:   PORTB
 *   A8-A15:  PORTA
 *   A16-A18: PD4, PD5, PD6
 *   WE#:     PD2
 *   OE#:     PD3
 *   CE#:     PD7
 *   D0-D7:   PORTC
 */

// Address lines
#define ADDR_LOW_PORT    PORTB
#define ADDR_LOW_DDR     DDRB
#define ADDR_MID_PORT    PORTA
#define ADDR_MID_DDR     DDRA
#define ADDR_HIGH_PORT   PORTD
#define ADDR_HIGH_DDR    DDRD
#define ADDR_HIGH_MASK   ((1 << PD4) | (1 << PD5) | (1 << PD6))

// Data bus
#define DATA_PORT        PORTC
#define DATA_DDR         DDRC

// Control signals on PORTD
#define CTRL_PORT        PORTD
#define CTRL_DDR         DDRD
#define FLASH_WE         (1 << PD2)
#define FLASH_OE         (1 << PD3)
#define FLASH_CE         (1 << PD7)

#define TIME_QUICK       1

// Corrected addresses for 0x5555 and 0x2AAA
static const address_t ADDR_5555 = { 0x55, 0x55, 0x00 }; // 0x5555
static const address_t ADDR_2AAA = { 0xAA, 0x2A, 0x00 }; // 0x2AAA

// Command bytes for programming
static const char sdp_data_program[3] = { 0xAA, 0x55, 0xA0 };
static const address_t sdp_addresses_program[3] = {
    // 1st cycle: 0x5555 -> 0xAA
    { 0x55, 0x55, 0x00 },
    // 2nd cycle: 0x2AAA -> 0x55
    { 0xAA, 0x2A, 0x00 },
    // 3rd cycle: 0x5555 -> 0xA0
    { 0x55, 0x55, 0x00 }
};

// Command bytes for erase
static const char sdp_data_erase[5] = { 0xAA, 0x55, 0x80, 0xAA, 0x55 };
static const address_t sdp_addresses_erase[5] = {
    // 1st cycle: 0x5555 -> 0xAA
    { 0x55, 0x55, 0x00 },
    // 2nd cycle: 0x2AAA -> 0x55
    { 0xAA, 0x2A, 0x00 },
    // 3rd cycle: 0x5555 -> 0x80
    { 0x55, 0x55, 0x00 },
    // 4th cycle: 0x5555 -> 0xAA
    { 0x55, 0x55, 0x00 },
    // 5th cycle: 0x2AAA -> 0x55
    { 0xAA, 0x2A, 0x00 }
};

void flash_init()
{
    ADDR_LOW_DDR = 0xFF;
    ADDR_MID_DDR = 0xFF;
    ADDR_HIGH_DDR |= ADDR_HIGH_MASK;
    
    CTRL_DDR |= FLASH_WE | FLASH_OE | FLASH_CE;
    
    DATA_DDR = 0xFF;
    
    // Idle state: WE# and OE# high (inactive), CE# low (active)
    CTRL_PORT |= FLASH_WE | FLASH_OE;
    CTRL_PORT &= ~FLASH_CE;
}

void flash_set_address(address_t *address)
{
    ADDR_LOW_PORT = address->low;
    ADDR_MID_PORT = address->middle;

    // Clear PD4-PD6
    ADDR_HIGH_PORT &= ~ADDR_HIGH_MASK;
    // Set PD4-PD6 from address->high
    ADDR_HIGH_PORT |= ((address->high & 0x07) << 4);

    flash_delay(TIME_QUICK);
}

// Generic function to send a sequence of writes (command bytes) to addresses
void flash_sdp(address_t *addresses, char *data, char count)
{
    for (char i = 0; i < count; i++)
    {
        flash_set_address(&addresses[i]);
        CTRL_PORT &= ~FLASH_WE;  // WE# low
        flash_delay(TIME_QUICK);
        DATA_PORT = data[i];     // put command on data bus
        flash_delay(TIME_QUICK);
        CTRL_PORT |= FLASH_WE;   // WE# high (latch data)
        flash_delay(TIME_QUICK);
    }
}

void flash_program(char data, address_t *address)
{
    // Unlock + command sequence (3 writes)
    flash_sdp((address_t*)sdp_addresses_program, (char*)sdp_data_program, 3);

    // Final write: target address -> data
    flash_sdp(address, &data, 1);

    // Restore
    flash_init();
}

char flash_read(address_t *address)
{
    flash_set_address(address);

    // Switch data bus to input
    DATA_DDR = 0x00;
    
    // OE# low to enable output
    CTRL_PORT &= ~FLASH_OE;
    char data = DATA_PORT; // read
    // Switch data bus back to output
    DATA_DDR = 0xFF;

    flash_init();
    return data;
}

void flash_erase(address_t *address)
{
    // Align address to 4KB sector
    address_t address_sector;
    address_sector.low = 0x00;
    address_sector.middle = address->middle & 0xF0; // clear lower nibble
    address_sector.high = address->high;

    // Unlock + erase command sequence (5 writes)
    flash_sdp((address_t*)sdp_addresses_erase, (char*)sdp_data_erase, 5);

    // Final erase command: sector address -> 0x30
    char sector_erase = 0x30;
    // Use the aligned address here, so the sector boundary is correct!
    flash_sdp(&address_sector, &sector_erase, 1);

    flash_delay(TIME_QUICK);

    flash_init();
}

void flash_delay(char count)
{
    // Approx. 2ms per count, just a rough busy-loop
    for (char i = 0; i < 0xFF; i++)
    {
        for (char j = 0; j < count; j++) {
            // no-op
        }
    }
}

