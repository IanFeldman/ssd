#ifndef NOR_H
#define NOR_H

#include <avr/io.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
    #endif

    typedef struct {
        uint8_t low;
        uint8_t middle;
        uint8_t high; // only lower 3 bits used
    } address_t;

    void flash_init(void);
    void flash_set_address(address_t *address);
    void flash_sdp(address_t *addresses, char *data, char count);
    void flash_program(char data, address_t *address);
    char flash_read(address_t *address);
    void flash_erase(address_t *address);
    void flash_delay(char count);

    #ifdef __cplusplus
}
#endif

#endif /* NOR_H */
