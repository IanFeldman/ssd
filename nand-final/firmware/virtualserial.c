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

#include <stdlib.h>
#include "virtualserial.h"
#include "lib/flash.h"
#include "lib/test.h"
#include "lib/uart.h"
#include "lib/util.h"

/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
    {
        .Config =
            {
                .ControlInterfaceNumber   = INTERFACE_ID_CDC_CCI,
                .DataINEndpoint           =
                    {
                        .Address          = CDC_TX_EPADDR,
                        .Size             = CDC_TXRX_EPSIZE,
                        .Banks            = 1,
                    },
                .DataOUTEndpoint =
                    {
                        .Address          = CDC_RX_EPADDR,
                        .Size             = CDC_TXRX_EPSIZE,
                        .Banks            = 1,
                    },
                .NotificationEndpoint =
                    {
                        .Address          = CDC_NOTIFICATION_EPADDR,
                        .Size             = CDC_NOTIFICATION_EPSIZE,
                        .Banks            = 1,
                    },
            },
    };

/** Standard file stream for the CDC interface when set up, so that the virtual CDC COM port can be
 *  used like any regular character stream in the C APIs.
 */
static FILE USBSerialStream;


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
    SetupHardware();

    /* Create a regular character stream for the interface so that it can be used with the stdio.h functions */
    CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);

    GlobalInterruptEnable();

    for (;;)
    {
        Poll();
        CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
        USB_USBTask();
    }
}


/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Disable clock division */
    clock_prescale_set(clock_div_1);

    /* Hardware Initialization */
    #ifdef UART
    uart_init();
    uart_print_esc(CLEAR_SCREEN);
    uart_print_esc(HOME_CURSOR);
    #endif
    flash_init();
    USB_Init();

    /* Clear virtual serial */
    SendEsc(CLEAR_SCREEN);
    SendEsc(HOME_CURSOR);
    SendPrefix();
}


/* Poll for user input. */
void Poll(void)
{
    static char command_buffer[CMD_BUFFER_SIZE];
    static int i = 0;

    int16_t received_byte = CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);
    if (received_byte >= 0)
    {
        char ch = (char)received_byte;

        /* submit line */
        if (ch == '\n' || ch == '\r' || i == CMD_BUFFER_SIZE - 1)
        {
            command_buffer[i] = '\0';
            ProcessLine(command_buffer, i);
            CDC_Device_Flush(&VirtualSerial_CDC_Interface);
            i = 0;
            return;
        }
        /* backspace */
        if ((ch == '\b' || ch  == 127))
        {
            if (i > 0)
            {
                SendEsc(RETREAT_CURSOR);
                CDC_Device_SendByte(&VirtualSerial_CDC_Interface, ' ');
                SendEsc(RETREAT_CURSOR);
                i--;
            }
            return;
        }
        /* disregard ansi escapes */
        if (ch == ESC_CHAR)
        {
            return;
        }
        /* save to buffer and echo back */
        command_buffer[i++] = ch;
        CDC_Device_SendByte(&VirtualSerial_CDC_Interface, ch);
    }
}


/* Process input string. */
void ProcessLine(char *buffer, int size)
{
    SendEsc(NEW_LINE);

    /* split line by spaces */
    char *token = strtok(buffer, " ");
    if (token != NULL)
    {
        /* usage: clear */
        if (!strcmp(token, CLEAR_CMD_STR))
        {
            CDC_Device_Flush(&VirtualSerial_CDC_Interface);
            SendEsc(CLEAR_SCREEN);
            SendEsc(HOME_CURSOR);
            SendPrefix();
            return;
        }
        /* usage: help */
        else if (!strcmp(token, HELP_CMD_STR))
        {
            ProcessHelp();
        }
        else if (!strcmp(token, READ_CMD_STR))
        {
            ProcessRead();
        }
        else if (!strcmp(token, WRITE_CMD_STR))
        {
            ProcessWrite();
        }
        else if (!strcmp(token, ERASE_CMD_STR))
        {
            ProcessErase();
        }
        else
        {
            CDC_Device_SendString(&VirtualSerial_CDC_Interface, "Unknown command");
            SendEsc(NEW_LINE);
        }
    }
    SendPrefix();
}


/* Process help command. */
void ProcessHelp(void)
{
    /* raid info */
    #ifdef RAID
    CDC_Device_SendString(&VirtualSerial_CDC_Interface,
        "RAID 1 enabled");
    SendEsc(NEW_LINE);
    #else
    CDC_Device_SendString(&VirtualSerial_CDC_Interface,
        "RAID 1 disabled");
    SendEsc(NEW_LINE);
    #endif

    /* uart info */
    #ifdef UART
    CDC_Device_SendString(&VirtualSerial_CDC_Interface,
        "UART enabled");
    SendEsc(NEW_LINE);
    #else
    CDC_Device_SendString(&VirtualSerial_CDC_Interface,
        "UART disabled");
    SendEsc(NEW_LINE);
    #endif

    CDC_Device_SendString(&VirtualSerial_CDC_Interface,
        "READ");
    SendEsc(NEW_LINE);
    CDC_Device_SendString(&VirtualSerial_CDC_Interface,
        "  usage: read [row] [column] [size]");
    SendEsc(NEW_LINE);
    CDC_Device_SendString(&VirtualSerial_CDC_Interface,
        "WRITE");
    SendEsc(NEW_LINE);
    CDC_Device_SendString(&VirtualSerial_CDC_Interface,
        "  usage: write [row] [column] [data]");
    SendEsc(NEW_LINE);
    CDC_Device_SendString(&VirtualSerial_CDC_Interface,
        "ERASE");
    SendEsc(NEW_LINE);
    CDC_Device_SendString(&VirtualSerial_CDC_Interface,
        "  usage: erase [row]");
    SendEsc(NEW_LINE);
}


/* Process read command.
 * usage: read row col size
 */
void ProcessRead(void)
{
    #ifdef RAID
    static int chip_id = 1;
    #endif
    char *row_str = strtok(NULL, " ");
    char *col_str = strtok(NULL, " ");
    char *siz_str = strtok(NULL, " ");
    /* check data is valid */
    if (!row_str || !col_str || !siz_str)
    {
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, "Invalid command");
        SendEsc(NEW_LINE);
        return;
    }
    if ((strlen(row_str) != ROW_STR_LEN) || (strlen(col_str) != COL_STR_LEN))
    {
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, "Invalid parameter lengths");
        SendEsc(NEW_LINE);
        return;
    }
    if (CheckHexPrefix(row_str) || CheckHexPrefix(col_str))
    {
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, "Invalid format");
        SendEsc(NEW_LINE);
        return;
    }

    uint32_t row = hex_str_to_int(row_str, 6);
    uint16_t col = hex_str_to_int(col_str, 4);
    uint16_t siz = (uint16_t)atoi(siz_str);

    /* check if address out of bounds */
    if (row >= ROW_MAX || col >= COL_MAX)
    {
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, "Address out of bounds");
        SendEsc(NEW_LINE);
        return;
    }

    /* determine size */
    int max_size = COL_MAX - col;
    if (siz > max_size)
    {
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, "Reading only to page boundary");
        SendEsc(NEW_LINE);
        siz = max_size;
    }

    #ifdef RAID
    uint32_t chip_row = row;
    #else
    /* divide by (64 * 4096) */
    uint32_t chip = row >> 18;
    uint32_t chip_row = row - (chip << 18);
    int chip_id = chip + 1;
    #endif

    /* keep usb alive */
    USB_USBTask();

    /* flash_pulse_debug(); */

    /* read data */
    uint8_t data[MAX_READ_SIZE];
    char byte[4] = { '\0', '\0', ' ', '\0' };
    int curr_width = 0;
    flash_enable(chip_id);
    /* do it in multiple batches if necessary */
    int bytes_read = 0;
    while (bytes_read < siz)
    {
        /* read */
        int bytes_to_read = min(siz - bytes_read, MAX_READ_SIZE);
        flash_read_batch(chip_row, col + bytes_read, chip_id, bytes_to_read, data);

        /* print */
        for (int i = 0; i < bytes_to_read; i++)
        {
            byte_to_hex_str(data[i], byte);
            CDC_Device_SendString(&VirtualSerial_CDC_Interface, byte);
            curr_width += 3; /* write three characters for each byte */
            if (curr_width >= TERMINAL_WIDTH)
            {
                SendEsc(NEW_LINE);
                curr_width = 0;
            }
        }

        bytes_read += bytes_to_read;
    }
    flash_disable(chip_id);

    /* flash_pulse_debug(); */

    SendEsc(NEW_LINE);

    #ifdef RAID
    /* move on to next chip */
    chip_id++;
    if (chip_id > CHIP_COUNT)
    {
        chip_id = 1;
    }
    #endif
}


/* Process write command.
 * usage: write row col data
 */
void ProcessWrite(void)
{
    char *row_str = strtok(NULL, " ");
    char *col_str = strtok(NULL, " ");
    char *dat_str = strtok(NULL, " ");
    /* check data is valid */
    if (!row_str || !col_str || !dat_str)
    {
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, "Invalid command");
        SendEsc(NEW_LINE);
        return;
    }
    if ((strlen(row_str) != ROW_STR_LEN) || (strlen(col_str) != COL_STR_LEN) ||
       (strlen(dat_str) != DATA_STR_LEN))
    {
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, "Invalid parameter lengths");
        SendEsc(NEW_LINE);
        return;
    }
    if (CheckHexPrefix(row_str) || CheckHexPrefix(col_str) || CheckHexPrefix(dat_str))
    {
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, "Invalid format");
        SendEsc(NEW_LINE);
        return;
    }

    uint32_t row = hex_str_to_int(row_str, 6);
    uint16_t col = hex_str_to_int(col_str, 4);
    uint8_t  dat = hex_str_to_int(dat_str, 2);

    /* check if address out of bounds */
    if (row >= ROW_MAX || col >= COL_MAX)
    {
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, "Address out of bounds");
        SendEsc(NEW_LINE);
        return;
    }

    /* keep usb alive */
    USB_USBTask();

    /* flash_pulse_debug(); */

    #ifdef RAID
    /* write data to all chips */
    for (int chip_id = 1; chip_id <= CHIP_COUNT; chip_id++)
    {
        flash_enable(chip_id);
        flash_program(row, col, &dat, 1, chip_id);
        flash_disable(chip_id);
    }
    #else
    /* write data to single chip */
    /* divide by (64 * 4096) */
    uint32_t chip = row >> 18;
    uint32_t chip_row = row - (chip << 18);
    int chip_id = chip + 1;
    flash_enable(chip_id);
    flash_program(chip_row, col, &dat, 1, chip_id);
    flash_disable(chip_id);
    #endif

    /* flash_pulse_debug(); */
}


/* Process erase command.
 * usage: erase row
 */
void ProcessErase(void)
{
    char *row_str = strtok(NULL, " ");
    /* check data is valid */
    if (!row_str)
    {
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, "Invalid command");
        SendEsc(NEW_LINE);
        return;
    }
    if (strlen(row_str) != ROW_STR_LEN)
    {
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, "Invalid parameter length");
        SendEsc(NEW_LINE);
        return;
    }
    if (CheckHexPrefix(row_str))
    {
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, "Invalid format");
        SendEsc(NEW_LINE);
        return;
    }

    /* check if address out of bounds */
    uint32_t row = hex_str_to_int(row_str, 6);
    if (row >= ROW_MAX)
    {
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, "Address out of bounds");
        SendEsc(NEW_LINE);
        return;
    }

    /* keep usb alive */
    USB_USBTask();

    /* flash_pulse_debug(); */

    #ifdef RAID
    /* erase on all chips */
    for (int chip_id = 1; chip_id <= CHIP_COUNT; chip_id++)
    {
        flash_enable(chip_id);
        flash_erase(row, chip_id);
        flash_disable(chip_id);
    }
    #else
    /* erase on single chip */
    /* divide by (64 * 4096) */
    uint32_t chip = row >> 18;
    uint32_t chip_row = row - (chip << 18);
    int chip_id = chip + 1;
    flash_enable(chip_id);
    flash_erase(chip_row, chip_id);
    flash_disable(chip_id);
    #endif

    /* flash_pulse_debug(); */
}


/* Return 0 if string has 0x or 0X at start, 1 if not */
int CheckHexPrefix(char *str)
{
    if (!str)
    {
        return 1;
    }
    int first = (str[0] == '0');
    int second = (str[1] == 'X' || str[1] == 'x');
    return !(first && second);
}


/* Send ANSI escape sequence */
void SendEsc(char *sequence)
{
    CDC_Device_SendByte(&VirtualSerial_CDC_Interface, ESC_CHAR);
    CDC_Device_SendString(&VirtualSerial_CDC_Interface, sequence);
}


/* Send '>' character. */
void SendPrefix(void)
{
    CDC_Device_SendString(&VirtualSerial_CDC_Interface, PREFIX);
}


/* Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
    #ifdef UART
    uart_print_ln("USB Connect");
    #endif
}


/* Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
    #ifdef UART
    uart_print_ln("USB Disconnect");
    #endif
}


/* Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
    #ifdef UART
    uart_print_ln("USB Config Changed");
    #endif

    bool ConfigSuccess = true;

    ConfigSuccess &= CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);
}


/* Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
    CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
}


/*  CDC class driver callback function the processing of changes to the virtual
 *  control lines sent from the host..
 *
 *  \param[in] CDCInterfaceInfo  Pointer to the CDC class interface configuration structure being referenced
 */
void EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_Device_t *const CDCInterfaceInfo)
{
    /* You can get changes to the virtual CDC lines in this callback; a common
       use-case is to use the Data Terminal Ready (DTR) flag to enable and
       disable CDC communications in your application when set to avoid the
       application blocking while waiting for a host to become ready and read
       in the pending data from the USB endpoints.
    */
    bool HostReady = (CDCInterfaceInfo->State.ControlLineStates.HostToDevice & CDC_CONTROL_LINE_OUT_DTR) != 0;

    (void)HostReady;
}

