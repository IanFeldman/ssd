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

#ifndef _DATAFLASH_MANAGER_H_
#define _DATAFLASH_MANAGER_H_

    #include <avr/io.h>

    #include "../storage.h"
    #include "../descriptors.h"
    #include "config/appconfig.h"

    #include <third_party/LUFA/Common/Common.h>
    #include <third_party/LUFA/Drivers/USB/USB.h>
    #include <third_party/LUFA/Drivers/Board/Dataflash.h>

    #define BLOCK_USE_SIZE 32
    #define VIRTUAL_MEMORY_BLOCK_SIZE 512

    /* TODO: change these */
    #define VIRTUAL_MEMORY_BYTES                ((uint32_t)DATAFLASH_PAGES * DATAFLASH_PAGE_SIZE * DATAFLASH_TOTALCHIPS)
    #define VIRTUAL_MEMORY_BLOCKS               (VIRTUAL_MEMORY_BYTES / VIRTUAL_MEMORY_BLOCK_SIZE)
    #define LUN_MEDIA_BLOCKS                    (VIRTUAL_MEMORY_BLOCKS / TOTAL_LUNS)

    void DataflashManager_WriteBlocks(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo,
                                      const uint32_t BlockAddress,
                                      uint16_t TotalBlocks);
    void DataflashManager_ReadBlocks(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo,
                                     const uint32_t BlockAddress,
                                     uint16_t TotalBlocks);
    void DataflashManager_WriteBlocks_RAM(const uint32_t BlockAddress,
                                          uint16_t TotalBlocks,
                                          uint8_t* BufferPtr) ATTR_NON_NULL_PTR_ARG(3);
    void DataflashManager_ReadBlocks_RAM(const uint32_t BlockAddress,
                                         uint16_t TotalBlocks,
                                         uint8_t* BufferPtr) ATTR_NON_NULL_PTR_ARG(3);
    void DataflashManager_ResetDataflashProtections(void);
    bool DataflashManager_CheckDataflashOperation(void);

#endif

