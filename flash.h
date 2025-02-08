#ifndef FLASH_H
#define FLASH_H

#define DATA_PORT P0
#define CTRL_PORT P3
#define WRITE_ENABLE 0x10
#define CHIP_ENABLE 0x20
#define OUTPUT_ENABLE 0x40

#define TIME_QUICK 0xFF

typedef struct {
    char high;
    char middle;
    char low;
} address_t;

void flash_init();
void flash_set_address(address_t *address);
void flash_program(char data, address_t *address);
char flash_read(address_t *address);
void flash_erase(address_t *address);
void flash_delay(char count);

#endif /* FLASH_H */

