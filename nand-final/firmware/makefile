#
#             LUFA Library
#     Copyright (C) Dean Camera, 2021.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

# Edited by Ian Feldman and Grayson Parker
# June 2025

MCU          = atmega32u2
ARCH         = AVR8
BOARD        = NONE
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = virtualserial
SRC          = $(TARGET).c descriptors.c lib/flash.c lib/test.c lib/uart.c \
               lib/util.c $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS)
LUFA_PATH    = third_party/LUFA
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig/
LD_FLAGS     =

# Add command line support for uart and raid
ifeq ($(UART),1)
CC_FLAGS += -DUART
endif

ifeq ($(RAID),1)
CC_FLAGS += -DRAID
endif

# Default target
all:

# Include LUFA-specific DMBS extension modules
DMBS_LUFA_PATH ?= $(LUFA_PATH)/Build/LUFA
include $(DMBS_LUFA_PATH)/lufa-sources.mk
include $(DMBS_LUFA_PATH)/lufa-gcc.mk

# Include common DMBS build system modules
DMBS_PATH      ?= $(LUFA_PATH)/Build/DMBS/DMBS
include $(DMBS_PATH)/gcc.mk

flash: $(TARGET).hex
	avrdude -c avrisp -P /dev/ttyACM0 -p m32u2 -b 19200 -U flash:w:$(TARGET).hex

restart: $(TARGET).hex
	avrdude -c avrisp -P /dev/ttyACM0 -p m32u2 -b 19200 -U flash:w:asdf.hex

fuses:
	avrdude -c avrisp -p m32u2 -P /dev/ttyACM0 -b 19200 -U lfuse:w:0xFF:m -U hfuse:w:0xD9:m -U efuse:w:0xF4:m

