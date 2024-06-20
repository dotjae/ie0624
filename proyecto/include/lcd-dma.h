#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/ltdc.h>

#include "clock.h"
#include "console.h"
#include "lcd-spi.h"
#include "sdram.h"

#define LCD_WIDTH  240
#define LCD_HEIGHT 320
#define REFRESH_RATE 70 /* Hz */

#define HSYNC       10
#define HBP         20
#define HFP         10

#define VSYNC        2
#define VBP          2
#define VFP          4

// Double buffering with layer1 and layer2.
// Layer2 is being displayed, layer2 is being built
typedef uint8_t layer1_pixel;
#define LCD_LAYER1_PIXFORMAT LTDC_LxPFCR_AL44
#define LCD_LAYER1_PIXEL_SIZE (sizeof(layer1_pixel))
#define LCD_LAYER1_WIDTH  LCD_WIDTH
#define LCD_LAYER1_HEIGHT LCD_HEIGHT
#define LCD_LAYER1_PIXELS (LCD_LAYER1_WIDTH * LCD_LAYER1_HEIGHT)
#define LCD_LAYER1_BYTES  (LCD_LAYER1_PIXELS * LCD_LAYER1_PIXEL_SIZE)

typedef uint8_t layer2_pixel;
#define LCD_LAYER2_PIXFORMAT LTDC_LxPFCR_AL44
#define LCD_LAYER2_PIXEL_SIZE (sizeof(layer2_pixel))
#define LCD_LAYER2_WIDTH  LCD_WIDTH
#define LCD_LAYER2_HEIGHT LCD_HEIGHT
#define LCD_LAYER2_PIXELS (LCD_LAYER2_WIDTH * LCD_LAYER2_HEIGH)
#define LCD_LAYER2_BYTES (LCD_LAYER2_PIXELS * LCD_LAYER2_PIXEL_SIZE)

void draw_pixel(int x, int y, uint8_t color);
void lcd_dma_init(void);
void show_frame(void);
