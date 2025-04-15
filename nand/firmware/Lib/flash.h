#ifndef FLASH_H
#define FLASH_H

#include <stdio.h>

#define F_CPU 16000000UL
#define CHIP_COUNT 4

/* port c, active low, outputs */
#define CHIP_ENABLE_1     (1 << PC2)
#define CHIP_ENABLE_2     (1 << PC5)
#define CHIP_ENABLE_3     (1 << PC4)
#define CHIP_ENABLE_4     (1 << PC6)
#define CHIP_ENABLE_DIR_1 (1 << DDC2)
#define CHIP_ENABLE_DIR_2 (1 << DDC5)
#define CHIP_ENABLE_DIR_3 (1 << DDC4)
#define CHIP_ENABLE_DIR_4 (1 << DDC6)

/* port c/d, active low, inputs (external pull up) */
#define READY_BUSY_1     (1 << PD7)
#define READY_BUSY_2     (1 << PD2)
#define READY_BUSY_3     (1 << PD3)
#define READY_BUSY_4     (1 << PC7)
#define READY_BUSY_DIR_1 (1 << DDD7)
#define READY_BUSY_DIR_2 (1 << DDD2)
#define READY_BUSY_DIR_3 (1 << DDD3)
#define READY_BUSY_DIR_4 (1 << DDC7)

/* port d outputs */
#define ADDR_LATCH       (1 << PD0) /* active high */
#define CMD_LATCH        (1 << PD1) /* active high */
#define READ_ENABLE      (1 << PD4) /* active low  */
#define WRITE_ENABLE     (1 << PD5) /* active low  */
#define WRITE_PROT       (1 << PD6) /* active low  */
#define ADDR_LATCH_DIR   (1 << DDD0)
#define CMD_LATCH_DIR    (1 << DDD1)
#define READ_ENABLE_DIR  (1 << DDD4)
#define WRITE_ENABLE_DIR (1 << DDD5)
#define WRITE_PROT_DIR   (1 << DDD6)

/* commands */
#define RESET_CMD            0xFF
#define READ_ID_CMD          0x90
#define READ_PAGE_CMD        0x00
#define END_READ_PAGE_CMD    0x30
#define RANDOM_READ_CMD      0x05
#define END_RANDOM_READ_CMD  0xE0
#define PROGRAM_PAGE_CMD     0x80
#define END_PROGRAM_PAGE_CMD 0x10
#define ERASE_BLOCK_CMD      0x60
#define END_ERASE_BLOCK_CMD  0xD0

void flash_init();
void flash_enable(int chip);
void flash_disable(int chip);
void flash_read_id(uint8_t *id, int chip);
uint8_t flash_read(uint32_t row, uint16_t column, int chip);
void flash_program(uint32_t row, uint16_t column,
    uint8_t *data, int size, int chip);
void flash_erase(uint32_t row, int chip);

#endif /* FLASH_H */

