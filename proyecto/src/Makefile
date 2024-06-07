PROJECT = firmware
BUILD_DIR = bin

SHARED_DIR += ../include/

# TODO: Fix all the CFILES includes
CFILES += main.c
CFILES += clock.c console.c font-7x12.c gfx.c lcd-spi.c sdram.c 
CFILES += button.c 
CFILES += qr.c chiles.c	pongMenu.c outline1.c outline2.c strings.c # imágenes
CFILES += pong.c mu.c pvp.c git.c # más imágenes
CFILES += Inicio.c 1.c 2.c 3.c inicio_outline.c
CFILES += fsm.c
CFILES += abort.c abort_outline.c

DEVICE=stm32f429zit6u
OOCD_FILE = board/stm32f4discovery.cfg

VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
