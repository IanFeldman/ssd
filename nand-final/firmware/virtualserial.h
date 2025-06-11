/*
             LUFA Library
     Copyright (C) Dean Camera, 2021.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2021  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 * June 2025
 */

#ifndef _VIRTUALSERIAL_H_
#define _VIRTUALSERIAL_H_

#define CMD_BUFFER_SIZE 128
#define PREFIX " > "
#define CLEAR_CMD_STR "clear"
#define HELP_CMD_STR  "help"
#define READ_CMD_STR  "read"
#define WRITE_CMD_STR "write"
#define ERASE_CMD_STR "erase"

#define MAX_READ_SIZE 256 /* size of read buffer */

#define TERMINAL_WIDTH 80
#define ROW_STR_LEN 8  /* 0x----   */
#define COL_STR_LEN 6  /* 0x------ */
#define DATA_STR_LEN 4 /* 0x--     */

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include "descriptors.h"
#include <LUFA/Drivers/USB/USB.h>

void SetupHardware(void);
void Poll(void);
void ProcessLine(char *buffer, int size);
void ProcessHelp(void);
void ProcessRead(void);
void ProcessWrite(void);
void ProcessErase(void);
int CheckHexPrefix(char *str);
void SendEsc(char *sequence);
void SendPrefix(void);
void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);

#endif

