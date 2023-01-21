# Makefile for ds18b20-serial

# Copyright David Haworth
# 
# This file is part of ds18b20-serial.
# 
# ds18b20-serial is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# ds18b20-serial is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with ds18b20-serial  If not, see <http://www.gnu.org/licenses/>.


AVR			?= t13

BUILD		?=	build
ISPPORT		?=	/dev/ttyUSB0
OBJ_DIR		?=	$(BUILD)/o
LIB_DIR		?=	$(BUILD)/a
TLIB_DIR	?=	../tiny-bare-metal/tinylib
TIO_DIR		?=	../tiny-bare-metal/tinyio
T1W_DIR		?=	../tiny-bare-metal/tiny1w

GCC			=	avr-gcc
GLD			=	avr-gcc
GAR			=	avr-ar
OBJCOPY		=	avr-objcopy

ifeq ($(AVR), t44)
GNU_MCU		:=	attiny44
HDR			:=	"\"ds18b20-t44.h\""
else ifeq ($(AVR), t85)
GNU_MCU		:=	attiny85
HDR			:=	"\"ds18b20-t85.h\""
else ifeq ($(AVR), t13)
GNU_MCU		:=	attiny13
HDR			:=	"\"ds18b20-t13.h\""
endif

CC_OPT		+=	-mmcu=$(GNU_MCU)
CC_OPT		+=	-D TINYLIB_CFG_HDR=$(HDR)
CC_OPT		+=	-fno-builtin
CC_OPT		+=	-Os
CC_OPT		+=	-g
CC_OPT		+=	-Wall
CC_OPT		+=	-I .
CC_OPT		+=	-I $(TLIB_DIR)
CC_OPT		+=	-I $(TIO_DIR)
CC_OPT		+=	-I $(T1W_DIR)

# Debugging
#CC_OPT		+= -D W1_PRESENCE=0
#CC_OPT		+= -D W1_DBG=1

LD_OPT		+=	-mmcu=$(GNU_MCU)
LD_OPT		+=	-Wl,--gc-sections
LD_OPT		+=	-Os
LD_OPT		+=	-L $(LIB_DIR)

LD_LIB		+=	-ltiny
LD_LIB		+=	-lm

OBJS		+=	$(OBJ_DIR)/ds18b20-serial.o

VPATH		+=	$(TLIB_DIR)
VPATH		+=	$(TIO_DIR)
VPATH		+=	$(T1W_DIR)

.PHONY:		default clean hex upload

default:	$(BUILD)/ds18b20-serial.elf

clean:
	if [ -d $(BUILD) ] ; then rm -r $(BUILD); fi

hex:		$(BUILD)/ds18b20-serial.ihex

$(BUILD)/o:
	mkdir -p $(BUILD)/o

$(BUILD)/ds18b20-serial.elf:	$(OBJ_DIR) $(OBJS) $(LIB_DIR)/libtiny.a
	$(GLD) $(LD_OPT) -o $@ $(OBJS) $(LD_LIB)
	

$(OBJ_DIR)/%.o:	%.c
	$(GCC) $(CC_OPT) -o $@ -c $<

$(BUILD)/ds18b20-serial.ihex:	$(BUILD)/ds18b20-serial.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

upload:		$(BUILD)/ds18b20-serial.ihex
	avrdude -P $(ISPPORT) -b 19200 -c avrisp -p $(AVR) -U flash:w:build/ds18b20-serial.ihex:i

include $(T1W_DIR)/tiny1w.make
include $(TIO_DIR)/tinyio.make
include $(TLIB_DIR)/tinylib.make
