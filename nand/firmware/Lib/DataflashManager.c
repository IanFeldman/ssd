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

/** \file
 *
 *  Functions to manage the physical Dataflash media, including reading and writing of
 *  blocks of data. These functions are called by the SCSI layer when data must be stored
 *  or retrieved to/from the physical storage media. If a different media is used (such
 *  as a SD card or EEPROM), functions similar to these will need to be generated.
 */

#define  INCLUDE_FROM_DATAFLASHMANAGER_C
#include "DataflashManager.h"

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
