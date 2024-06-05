PROJECT = firmware
BUILD_DIR = bin

SHARED_DIR += ../include/lcd-serial
SHARED_DIR += ../include/button
SHARED_DIR += ../include/pong
SHARED_DIR += ../include/images

CFILES += main.c
CFILES += clock.c console.c font-7x12.c gfx.c lcd-spi.c sdram.c 
CFILES += button.c
CFILES += qr.c chiles.c	pongMenu.c # imágenes

DEVICE=stm32f429zit6u
OOCD_FILE = board/stm32f4discovery.cfg

VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
