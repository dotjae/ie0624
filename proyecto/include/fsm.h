#include <stdint.h>
#include <stdbool.h>
#include <libopencm3/stm32/gpio.h>
#include "lcd-spi.h"
#include "clock.h"
#include "gfx.h"
#include "images.h"

void menu_fsm(void);
