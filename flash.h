#ifndef FLASH_H
#define FLASH_H

#define DATA_PORT P0
#define WRITE_ENABLE 0x10
#define CHIP_ENABLE 0x20
#define OUTPUT_ENABLE 0x40

typedef struct {
    char high;
    char middle;
    char low;
} address_t;

void flash_init();
void flash_set_address(address_t *address);
void flash_program(char data, address_t *address);
char flash_read(address_t *address);
void flash_delay();

#endif /* FLASH_H */

