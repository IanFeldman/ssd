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

#include "virtualserial.h"
#include "lib/flash.h"
#include "lib/test.h"
#include "lib/uart.h"

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
    uart_init();
    flash_init();
    USB_Init();

    /* Clear uart terminal */
    uart_print_esc(CLEAR_SCREEN);
    uart_print_esc(HOME_CURSOR);

    /* Clear virtual serial */
    SendEsc(CLEAR_SCREEN);
    SendEsc(HOME_CURSOR);
    SendPrefix();

    /* Test flash */
    // test_all();
}

void Poll(void)
{
    static char command_buffer[CMD_BUFFER_SIZE];
    static int i = 0;

    int16_t received_byte = CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);
    if (received_byte >= 0)
    {
        char ch = (char)received_byte;

        /* submit line */
        if (ch == '\n' || ch == '\r')
        {
            ProcessLine(command_buffer, i);
            i = 0;
        }
        /* save to buffer and echo back */
        else
        {
            command_buffer[i++] = ch;
            CDC_Device_SendByte(&VirtualSerial_CDC_Interface, ch);
        }
        /* auto-process if buffer is full */
        if (i == CMD_BUFFER_SIZE)
        {
            ProcessLine(command_buffer, i);
            i = 0;
        }
    }
}

void ProcessLine(char *buffer, int size)
{
    uart_print_ln("Processing line");
    SendEsc(NEW_LINE);
    SendPrefix();

    /* split line by spaces */
    char *token = strtok(buffer, " ");
    if (token != NULL)
    {
        /* usage: clear */
        if (!strcmp(token, CLEAR_CMD_STR))
        {
            uart_print_ln("CLEAR");
            SendEsc(CLEAR_SCREEN);
            SendEsc(HOME_CURSOR);
            SendPrefix();
            return;
        }
        /* usage: help */
        if (!strcmp(token, HELP_CMD_STR))
        {
            CDC_Device_SendString(&VirtualSerial_CDC_Interface, "USAGE\n");
            return;
        }
        /* usage: read column row size */
        if (!strcmp(token, READ_CMD_STR))
        {
            uart_print_ln("Read");
            char *column = strtok(NULL, " ");
            char *row = strtok(NULL, " ");
            char *size = strtok(NULL, " ");
            return;
        }
        if (!strcmp(token, WRITE_CMD_STR))
        {
            return;
        }
        if (!strcmp(token, ERASE_CMD_STR))
        {
            return;
        }

        token = strtok(NULL, " ");
    }
    else
    {
        CDC_Device_SendString(&VirtualSerial_CDC_Interface, "Usage error\n");
    }
}

/* Send ANSI escape sequence */
void SendEsc(char *sequence)
{
    CDC_Device_SendByte(&VirtualSerial_CDC_Interface, ESC_CHAR);
    CDC_Device_SendString(&VirtualSerial_CDC_Interface, sequence);
}

void SendPrefix(void)
{
    CDC_Device_SendString(&VirtualSerial_CDC_Interface, PREFIX);
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
    uart_print_ln("USB Connect");
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
    uart_print_ln("USB Disconnect");
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
    uart_print_ln("USB Changed");

    bool ConfigSuccess = true;

    ConfigSuccess &= CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
    CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
}

/** CDC class driver callback function the processing of changes to the virtual
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
