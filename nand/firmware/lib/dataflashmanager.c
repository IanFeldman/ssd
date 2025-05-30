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
 * 1. The first page of every block indicates if the block is used or not.
 *      + All 0xFF: unused
 *      + All 0x00: used
 * 2. Receive some data to write from usb.
 * 3. Find the physical block in flash.
 * 4. If that block is unused, just write data to it.
 * 5. If the block is used, read each page individually,
 *    and write it to the next free block (include new page data).
 * 6. Erase the first block and copy it the new one back.
 *      + Ideally we would map logical to physical blocks, but
 *        there is not enough space to do this.
 */

#define  INCLUDE_FROM_DATAFLASHMANAGER_C
#include "dataflashmanager.h"
#include "flash.h"

static uint8_t page_temp_g[PAGE_SIZE];

/* Check if block is used. Pass in address row and chip. */
static int BlockUsed(uint32_t block_row, int chip)
{
    uint8_t data[BLOCK_USE_SIZE];
    memset(data, 0x00, BLOCK_USE_SIZE);
    flash_read_batch(block_row, 0x0000, chip, BLOCK_USE_SIZE, data);

    int used = 0xFF;
    for (int i = 0; i < BLOCK_USE_SIZE; i++)
    {
        used &= data[i];
    }
    return !used;
}


/** Writes blocks (OS blocks, not Dataflash pages) to the storage medium, the board Dataflash IC(s), from
 *  the pre-selected data OUT endpoint. This routine reads in OS sized blocks from the endpoint and writes
 *  them to the Dataflash in Dataflash page sized blocks.
 *
 *  \param[in] MSInterfaceInfo  Pointer to a structure containing a Mass Storage Class configuration and state
 *  \param[in] BlockAddress  Data block starting address for the write sequence
 *  \param[in] TotalBlocks   Number of blocks of data to write
 */
void DataflashManager_WriteBlocks(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo,
                                  const uint32_t BlockAddress,
                                  uint16_t TotalBlocks)
{
    /* compute absolute byte offset into virtual memory */
    uint32_t byte_address = BlockAddress * VIRTUAL_MEMORY_BLOCK_SIZE;

    /* compute which usable page (excluding reserved pages) */
    uint32_t usable_page_index = byte_address / PAGE_SIZE;

    /* determine which block this maps to */
    uint16_t flash_block = usable_page_index / USABLE_PAGES_PER_BLOCK;

    /* determine which usable page within that block */
    uint32_t page_in_block = usable_page_index % USABLE_PAGES_PER_BLOCK;

    /* select correct chip (idx at 1) */
    int chip_id = (flash_block / BLOCKS_PER_CHIP) + 1;

    /* block index within chip */
    uint16_t block_on_chip = flash_block % BLOCKS_PER_CHIP;

    /* final flash row (add +1 to skip reserved page 0 in each block) */
    uint32_t page_on_chip = block_on_chip * PAGES_PER_BLOCK + (page_in_block + 1);

    /* final flash column */
    uint16_t byte_on_page = byte_address % PAGE_SIZE;

    /* enable chip */
    flash_enable(chip_id);

    /* page of start of the target block */
    uint32_t target_block_start_page = block_on_chip * PAGES_PER_BLOCK;
    uint32_t temp_block_start_page   = target_block_start_page;

    /* find free block */
    while (BlockUsed(temp_block_start_page, chip_id))
    {
        temp_block_start_page += PAGES_PER_BLOCK;
    }

    /* now we have found a free block */
    /* if the block we found is different than the target */
    if (temp_block_start_page != target_block_start_page)
    {
        /* copy pages over to this new block */
        for (int page = 0; page < USABLE_PAGES_PER_BLOCK; page++)
        {
            /* start after reserved page */
            uint32_t old_page = target_block_start_page + page + 1;
            uint32_t new_page = temp_block_start_page + page + 1;

            /* if this is the page we want to overwrite */
            if (page == page_in_block)
            {
                /* read new data directly from USB */
                Endpoint_Read_Stream_LE(page_temp_g, PAGE_SIZE, NULL);
            }
            else
            {
                /* copy existing page from original block */
                flash_read_batch(old_page, 0x0000, chip_id, PAGE_SIZE, page_temp_g);
            }

            /* write page */
            flash_program(new_page, 0x0000, page_temp_g, PAGE_SIZE, chip_id);
        }

        /* erase original block */
        flash_erase(target_block_start_page, chip_id);

        /* copy temp block back to target*/
        for (int page = 0; page < USABLE_PAGES_PER_BLOCK; page++)
        {
            /* start after reserved page */
            uint32_t old_page = target_block_start_page + page + 1;
            uint32_t new_page = temp_block_start_page + page + 1;

            /* read page */
            flash_read_batch(new_page, 0x0000, chip_id, PAGE_SIZE, page_temp_g);
            /* write page */
            flash_program(old_page, 0x0000, page_temp_g, PAGE_SIZE, chip_id);
        }

        /* reset temp block */
        flash_erase(temp_block_start_page, chip_id);
    }
    /* if the block we found is target */
    else
    {
        /* program the exact spot we want to */
        Endpoint_Read_Stream_LE(page_temp_g, PAGE_SIZE, NULL);
        flash_program(page_on_chip, byte_on_page, page_temp_g, PAGE_SIZE, chip_id);
        /* mark the block as used by setting first page to zeros */
        memset(page_temp_g, 0x00, PAGE_SIZE);
        flash_program(target_block_start_page, 0x0000, page_temp_g, PAGE_SIZE, chip_id);
    }

    flash_disable(chip_id);
}


/** Reads blocks (OS blocks, not Dataflash pages) from the storage medium, the board Dataflash IC(s), into
 *  the pre-selected data IN endpoint. This routine reads in Dataflash page sized blocks from the Dataflash
 *  and writes them in OS sized blocks to the endpoint.
 *
 *  \param[in] MSInterfaceInfo  Pointer to a structure containing a Mass Storage Class configuration and state
 *  \param[in] BlockAddress  Data block starting address for the read sequence
 *  \param[in] TotalBlocks   Number of blocks of data to read
 */
void DataflashManager_ReadBlocks(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo,
                                 const uint32_t BlockAddress,
                                 uint16_t TotalBlocks)
{
    uint8_t buffer[VIRTUAL_MEMORY_BLOCK_SIZE];

    for (int i = 0; i < TotalBlocks; i++)
    {
        uint32_t byte_offset = (BlockAddress + i) * VIRTUAL_MEMORY_BLOCK_SIZE;

        uint32_t usable_page_index = byte_offset / PAGE_SIZE;
        uint16_t flash_block       = usable_page_index / USABLE_PAGES_PER_BLOCK;
        uint32_t page_in_block     = usable_page_index % USABLE_PAGES_PER_BLOCK;
        int chip_id                = (flash_block / BLOCKS_PER_CHIP) + 1;
        uint16_t block_on_chip     = flash_block % BLOCKS_PER_CHIP;
        uint32_t page_on_chip      = block_on_chip * PAGES_PER_BLOCK + (page_in_block + 1);
        uint16_t byte_on_page      = byte_offset % PAGE_SIZE;

        flash_enable(chip_id);

        flash_read_batch(page_on_chip, byte_on_page, chip_id, VIRTUAL_MEMORY_BLOCK_SIZE, buffer);
        Endpoint_Write_Stream_LE(buffer, VIRTUAL_MEMORY_BLOCK_SIZE, NULL);

        flash_disable(chip_id);
    }
}


/** Disables the Dataflash memory write protection bits on the board Dataflash ICs, if enabled. */
void DataflashManager_ResetDataflashProtections(void)
{
}


/** Performs a simple test on the attached Dataflash IC(s) to ensure that they are working.
 *
 *  \return Boolean \c true if all media chips are working, \c false otherwise
 */
bool DataflashManager_CheckDataflashOperation(void)
{
    return true;
}

