/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/*
 * Edited by Ian Feldman and Grayson Parker
 * May 2025
 */

/*
 * Just use blocks.
 * virtual os block = physical block
 * Read and write to first 512 bytes in each block
 */

#define  INCLUDE_FROM_DATAFLASHMANAGER_C
#include "dataflashmanager.h"
#include "flash.h"
#include "uart.h"

void DataflashManager_WriteBlocks(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo,
                                  const uint32_t BlockAddress,
                                  uint16_t TotalBlocks)
{
    /* wait until endpoint is ready before continuing */
    if (Endpoint_WaitUntilReady())
    {
        return;
    }

    uart_print_ln("Writing blocks");
    for (uint16_t i = 0; i < TotalBlocks; i++)
    {
        /* calculate the page address */
        uint32_t block_number = BlockAddress + i;
        uint32_t page_address = block_number * PAGES_PER_BLOCK;

        /* find the chip */
        int chip_id = (block_number / BLOCKS_PER_CHIP) + 1;
        flash_enable(chip_id);

        /* erase block in flash */
        flash_erase(page_address, chip_id);

        /* write in 16 byte increments */
        uint16_t bytes_in_block_div16 = 0;
        while (bytes_in_block_div16 < (VIRTUAL_MEMORY_BLOCK_SIZE >> 4))
        {
            /* check if the endpoint is currently empty */
            if (!(Endpoint_IsReadWriteAllowed()))
            {
                    /* clear the current endpoint bank */
                    Endpoint_ClearOUT();

                    /* wait until the host has sent another packet */
                    if (Endpoint_WaitUntilReady())
                    {
                        flash_disable(chip_id);
                        uart_print_ln("Aborting command");
                        return;
                    }
            }

            /* read in 16 bytes from endpoint */
            uint8_t chunk[16];
            for (uint8_t j = 0; j < 16; j++)
            {
                chunk[j] = Endpoint_Read_8();
            }

            /* program block in flash with new data */
            flash_program(page_address, bytes_in_block_div16 << 4, chunk, 16, chip_id);

            bytes_in_block_div16++;

            /* check if the current command is being aborted by the host */
            if (MSInterfaceInfo->State.IsMassStoreReset)
            {
                flash_disable(chip_id);
                uart_print_ln("Aborting command");
                return;
            }
        }

        flash_disable(chip_id);
    }

    if (!(Endpoint_IsReadWriteAllowed()))
    {
        Endpoint_ClearOUT();
    }

    uart_print_ln("Write complete");
}


void DataflashManager_ReadBlocks(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo,
                                 const uint32_t BlockAddress,
                                 uint16_t TotalBlocks)
{
    /* wait until endpoint is ready before continuing */
    if (Endpoint_WaitUntilReady())
    {
        return;
    }

    uart_print_ln("Reading blocks");
    for (uint16_t i = 0; i < TotalBlocks; i++)
    {
        /* calculate the page address */
        uint32_t block_number = BlockAddress + i;
        uint32_t page_address = block_number * PAGES_PER_BLOCK;

        /* find the chip */
        int chip_id = (block_number / BLOCKS_PER_CHIP) + 1;
        flash_enable(chip_id);

        /* read in 16 byte increments */
        uint16_t bytes_in_block_div16 = 0;
        while (bytes_in_block_div16 < (VIRTUAL_MEMORY_BLOCK_SIZE >> 4))
        {
            /* check if the endpoint is currently empty */
            if (!(Endpoint_IsReadWriteAllowed()))
            {
                    /* clear the current endpoint bank */
                    Endpoint_ClearIN();

                    /* wait until the host has sent another packet */
                    if (Endpoint_WaitUntilReady())
                    {
                        uart_print_ln("Aborting command");
                        flash_disable(chip_id);
                        return;
                    }
            }

            /* read in 16 bytes from flash */
            uint8_t chunk[16];
            flash_read_batch(page_address, bytes_in_block_div16 << 4, chip_id, 16, chunk);

            /* write to endpoint */
            for (uint8_t j = 0; j < 16; j++)
            {
                Endpoint_Write_8(chunk[j]);
            }

            bytes_in_block_div16++;

            /* check if the current command is being aborted by the host */
            if (MSInterfaceInfo->State.IsMassStoreReset)
            {
                uart_print_ln("Aborting command");
                flash_disable(chip_id);
                return;
            }
        }

        flash_disable(chip_id);
    }

    if (!(Endpoint_IsReadWriteAllowed()))
    {
        Endpoint_ClearIN();
    }

    uart_print_ln("Read complete");
}


/* Test ICs to make sure they are working */
bool DataflashManager_CheckDataflashOperation(void)
{
    /* TODO */
    return true;
}

