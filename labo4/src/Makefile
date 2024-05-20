PROJECT = firmware
BUILD_DIR = bin

SHARED_DIR = ../include 
CFILES = pendientes.c
CFILES += clock.c console.c font-7x12.c gfx.c lcd-spi.c sdram.c
# AFILES += api-asm.S

# TODO - you will need to edit these two lines! ojo
DEVICE=stm32f407vgt6
OOCD_FILE = board/stm32f4discovery.cfg

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
