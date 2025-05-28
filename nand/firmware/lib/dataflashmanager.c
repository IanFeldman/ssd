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
    /* raw byte address */
    uint32_t byte_address = BlockAddress * VIRTUAL_MEMORY_BLOCK_SIZE;
    /* raw block */
    uint16_t flash_block = byte_address / (PAGES_PER_BLOCK * PAGE_SIZE);
    /* select correct chip (idx at 0) */
    int chip = flash_block / BLOCKS_PER_CHIP;
    /* block on chip */
    uint16_t flash_block_chip = flash_block - chip * BLOCKS_PER_CHIP;
    /* row */
    uint32_t flash_page_chip = (byte_address / PAGE_SIZE) - (chip * BLOCKS_PER_CHIP * PAGES_PER_BLOCK);
    /* column */
    uint16_t flash_offset_chip = byte_address % PAGE_SIZE;

    /* enable chip (idx at 1 )*/
    int chip_id = chip + 1;
    flash_enable(chip_id);

    /* check if block has been written to */
    uint32_t flash_block_row = flash_block_chip * PAGES_PER_BLOCK;
    uint32_t flash_block_row_temp = flash_block_row;
    while (BlockUsed(flash_block_row_temp, chip_id))
    {
        flash_block_row_temp = flash_block_row + PAGES_PER_BLOCK;
    }

    /* now we have found a free block */
    /* if the block we found is different than the target */
    if (flash_block_row_temp != flash_block_row)
    {
        /* copy pages over to this new block */
        for (int page = 0; page < PAGES_PER_BLOCK; page++)
        {
            uint32_t old_row = flash_block_row + page;
            uint32_t new_row = flash_block_row_temp + page;

            /* if this is the page we want to overwrite */
            if (page == (flash_page_chip % PAGES_PER_BLOCK))
            {
                /* read new data directly from USB */
                Endpoint_Read_Stream_LE(page_temp_g, PAGE_SIZE, NULL);
            }
            else
            {
                /* copy existing page from original block */
                flash_read_batch(old_row, 0x0000, chip_id, PAGE_SIZE, page_temp_g);
            }

            /* write page */
            flash_program(new_row, 0x0000, page_temp_g, PAGE_SIZE, chip_id);
        }

        /* erase original block */
        flash_erase(flash_block_row, chip_id);

        /* copy free block back */
        for (int page = 0; page < PAGES_PER_BLOCK; page++)
        {
            uint32_t old_row = flash_block_row + page;
            uint32_t new_row = flash_block_row_temp + page;

            flash_read_batch(old_row, 0x0000, chip_id, PAGE_SIZE, page_temp_g);
        }

        /* reset temp block */
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
}

/** Writes blocks (OS blocks, not Dataflash pages) to the storage medium, the board Dataflash IC(s), from
 *  the given RAM buffer. This routine reads in OS sized blocks from the buffer and writes them to the
 *  Dataflash in Dataflash page sized blocks. This can be linked to FAT libraries to write files to the
 *  Dataflash.
 *
 *  \param[in] BlockAddress  Data block starting address for the write sequence
 *  \param[in] TotalBlocks   Number of blocks of data to write
 *  \param[in] BufferPtr     Pointer to the data source RAM buffer
 */
void DataflashManager_WriteBlocks_RAM(const uint32_t BlockAddress,
                                      uint16_t TotalBlocks,
                                      uint8_t* BufferPtr)
{
}

/** Reads blocks (OS blocks, not Dataflash pages) from the storage medium, the board Dataflash IC(s), into
 *  the preallocated RAM buffer. This routine reads in Dataflash page sized blocks from the Dataflash
 *  and writes them in OS sized blocks to the given buffer. This can be linked to FAT libraries to read
 *  the files stored on the Dataflash.
 *
 *  \param[in] BlockAddress  Data block starting address for the read sequence
 *  \param[in] TotalBlocks   Number of blocks of data to read
 *  \param[out] BufferPtr    Pointer to the data destination RAM buffer
 */
void DataflashManager_ReadBlocks_RAM(const uint32_t BlockAddress,
                                     uint16_t TotalBlocks,
                                     uint8_t* BufferPtr)
{
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
