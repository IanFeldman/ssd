#ifndef FLASH_H
#define FLASH_H

#include <stdio.h>

#define F_CPU 16000000UL

#define CHIP_ENABLE (1 << PC2)
#define ADDR_LATCH (1 << PD0)
#define CMD_LATCH (1 << PD1)
#define READ_ENABLE (1 << PD4)
#define WRITE_ENABLE (1 << PD5)
#define WRITE_PROT (1 << PD6)
#define READY_BUSY (1 << PD7)

void flash_init();
void flash_read_id(uint8_t *id);
void flash_read_page(uint8_t *data);

#endif /* FLASH_H */

