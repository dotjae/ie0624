#include <stdbool.h>
#include "clock.h"
#include "console.h"
#include "sdram.h"
#include "lcd-spi.h"
#include "gfx.h"
#include "button.h"
#include "images.h"

#define LINE_HEIGHT 15

void menu_fsm(void);
