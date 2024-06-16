#include <stdint.h>
#include <stdbool.h>
#include <libopencm3/stm32/gpio.h>
#include "lcd-spi.h"
#include "clock.h"
#include "gfx.h"
#include "images.h"

#define LINE_HEIGHT 20

void menu_fsm(void);
void ball_update(void);
uint8_t dumb_agent(int16_t x, int16_t y, int16_t dx, int16_t dy);
