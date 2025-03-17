#!/bin/bash
avrdude -c stk500v1 -p m32u2 -P /dev/ttyACM0 -b 19200 -U lfuse:w:0xFF:m -U hfuse:w:0xD7:m

