#ifndef FLASH_H
#define FLASH_H

#include <stdio.h>

#define F_CPU 16000000UL

/* pins */
#define CHIP_ENABLE (1 << PC2)
#define ADDR_LATCH (1 << PD0)
#define CMD_LATCH (1 << PD1)
#define READ_ENABLE (1 << PD4)
#define WRITE_ENABLE (1 << PD5)
#define WRITE_PROT (1 << PD6)
#define READY_BUSY (1 << PD7)

/* commands */
#define READ_ID_CMD 0x90
#define READ_PAGE_CMD 0x00
#define END_READ_PAGE_CMD 0x30
#define RANDOM_READ_CMD 0x05
#define END_RANDOM_READ_CMD 0xE0
#define PROGRAM_PAGE_CMD 0x80
#define END_PROGRAM_PAGE_CMD 0x10

void flash_init();
void flash_read_id(uint8_t *id);
uint8_t flash_read(uint32_t address, uint16_t column);
void flash_program(uint32_t address, uint16_t column,
    uint8_t data);

#endif /* FLASH_H */

