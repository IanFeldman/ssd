# ssd
2025 Cal Poly EE/CPE senior project exploring nonvolatile flash storage. Includes a [prototype design](#nor) using an 8051 and small NOR flash IC and the [final design](#nand) with a modern Atmel microcontroller and multiple high-density NAND flash ICs on a custom PCB.

## nand
4Gb NAND flash memory board with virtual serial interface over USB. Supports default and RAID 1 configurations.

### Firmware Build and Flash Instructions (Linux)
```sh
# Install dependencies
sudo apt install gcc-avr avr-libc avrdude make

# Clone this repo
git clone https://github.com/IanFeldman/ssd.git
cd ssd/nand/firmware

# Burn fuses (first time only)
make fuses

# Compile and flash firmware using ISP
# (edit makefile as needed)
make [UART=1] [RAID=1] # Optionally enable UART debugging or RAID 1
make flash
```

UART debugging interferes with some NAND chip control lines. Enable it at your own risk.\
RAID is performed across all 4 chips, so it decreases the address space fourfold.

### Usage:
Plug PCB into PC USB port and open a terminal with:\
```screen /dev/[path-to-usb-device] -b 9600```

### Commands:
<table>

<tr>
<td>Command</td>
<td>Usage</td>
<td>Function</td>
</tr>
<tr>
<td>Help</td>
<td>
  
```help```
</td>
<td>Displays device info and a list of commands.</td>
</tr>
<tr>
<td>Read</td>
<td>
  
```read 0x[row] 0x[column] [size]```
</td>
<td>Reads [size] bytes from memory.<br>A device will not read across a page boundary.</td>
</tr>
<tr>
<td>Write</td>
<td>
  
```write 0x[row] 0x[column] 0x[data]```
</td>
<td>Writes a single byte [data] to memory.</td>
</tr>
<tr>
<td>Erase</td>
<td>
  
```erase 0x[row]```
</td>
<td>Erases a block from memory.</td>
</tr>
</table>

Note:
- ```[row]``` is three bytes and represents a page address. Max value: 0x0FFFFF (0x040000 with RAID enabled).
- ```[column]``` is two bytes and represents a page offset in bytes. Max value: 0x07FF.
- ```[data]``` is one byte.
- ```[size]``` is a decimal unsigned integer.


## nor
Prototype breadboard 512kB flash memory storage device. Interface over UART at 9600 baud. Compile with SDCC and program with avrdude. See hardware schematic for hardware details.

### Firmware Build and Flash Instructions (Linux)
```sh
# Install dependencies
sudo apt install sdcc

# Clone this repo
git clone https://github.com/IanFeldman/ssd.git
cd ssd/nor/firmware

# Compile and flash firmware using ISP
make
./program.sh
```

### Usage:
Connect a serial cable to ```RXD``` and ```TXD``` on the microcontroller. Open a terminal with:\
```screen /dev/[path-to-serial-cable] -b 9600```

### Commands:
- Read an address ```r[address]```
- Erase an address ```e[address]```
- Program an address ```p[address][data]```

Where:
- ```[address]``` is 3 hex bytes
- ```[data]``` is one hex byte
