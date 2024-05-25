PROJECT = firmware
BUILD_DIR = bin

SHARED_DIR = ../include/gyro
SHARED_DIR += ../include/lcd
SHARED_DIR += ../include/labo4
CFILES = pendientes.c
CFILES += clock.c console.c font-7x12.c gfx.c lcd-spi.c sdram.c lcd_pendientes.c 
# AFILES += api-asm.S

# TODO - you will need to edit these two lines! ojo
DEVICE=stm32f429zit6u
OOCD_FILE = board/stm32f4discovery.cfg

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
