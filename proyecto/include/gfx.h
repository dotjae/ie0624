/*
 * A simple port of the AdaFruit minimal graphics code to my
 * demo code.
 */
#ifndef _GFX_H
#define _GFX_H
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "images.h"

#define swap(a, b) { int32_t t = a; a = b; b = t; }

void gfx_drawPixel(int x, int y, uint32_t color);
void gfx_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		  uint32_t color);
void gfx_drawFastVLine(int16_t x, int16_t y, int16_t h, uint32_t color);
void gfx_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color);
void gfx_fillScreen(uint32_t color);
void gfx_init(void (*draw)(int, int, uint32_t), int, int);
void gfx_drawBitmap(int16_t x, int16_t y, tImage bmp);
void gfx_fillCircle(int16_t x0, int16_t y0, int16_t r,
		    uint32_t color);
void gfx_fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint32_t color);
void gfx_drawChar(int16_t x, int16_t y, unsigned char c,
		  uint32_t color, uint32_t bg, uint8_t size);
void gfx_write(uint8_t c);
void gfx_puts(char *s);
void gfx_setCursor(int16_t x, int16_t y);
void gfx_setTextSize(uint8_t s);
void gfx_setTextColor(uint32_t color, uint32_t bg);
void gfx_setTextWrap(uint8_t w);
uint8_t gfx_getRotation(void);
void gfx_setRotation(uint8_t x);
uint16_t gfx_width(void);
uint16_t gfx_height(void);
void gfx_fillRoundRect(int16_t x, int16_t y, int16_t w,
		       int16_t h, int16_t r, uint32_t color);
void gfx_box(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, int16_t line_w);
#define GFX_WIDTH   320
#define GFX_HEIGHT  240

struct gfx_state {
	int16_t _width, _height, cursor_x, cursor_y;
	uint32_t textcolor, textbgcolor;
	uint8_t textsize, rotation;
	uint8_t wrap;
	void (*drawpixel)(int, int, uint32_t);
};

extern struct gfx_state __gfx_state;

#define GFX_BLACK          0x00000000
#define GFX_WHITE          0xffffffff


#endif /* _ADAFRUIT_GFX_H */
