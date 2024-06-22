PROJECT = firmware
BUILD_DIR = bin

# headers and bmps
SHARED_DIR += ../include/
SHARED_DIR += ../bitmaps/

# peripheral init files 
CFILES += button.c clock.c console.c lcd-dma.c lcd-spi.c sdram.c random.c

# source code 
CFILES += fsm.c gfx.c main.c 

DEVICE=stm32f429zit6u
OOCD_FILE = board/stm32f4discovery.cfg

VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
