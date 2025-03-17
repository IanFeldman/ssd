#!/bin/bash
avrdude -c stk500v1 -P /dev/ttyACM0 -p m32u2 -b 19200 -U flash:w:$1

