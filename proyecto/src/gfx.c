/*
 * This is the core graphics library for all our displays, providing a common
 * set of graphics primitives (points, lines, circles, etc.).  It needs to be
 * paired with a hardware-specific library for each display device we carry
 * (to handle the lower-level functions).
 *
 * Adafruit invests time and resources providing this open source code, please
 * support Adafruit & open-source hardware by purchasing products from Adafruit!
 *
 * Copyright (c) 2013 Adafruit Industries.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Modified the AdaFruit library to be a C library, changed the font and
 * generally munged it in a variety of ways, creating a reasonably quick
 * and dirty way to put something "interesting" on the LCD display.
 * --Chuck McManis (2013, 2014)
 *
 */

#include "gfx.h"

#define pgm_read_double_word(addr) (*(const uint32_t *)(addr))

struct gfx_state __gfx_state;

void
gfx_drawPixel(int x, int y, uint32_t color)
{
	if ((x < 0) || (x >= __gfx_state._width) ||
	    (y < 0) || (y >= __gfx_state._height)) {
		return; /* off screen so don't draw it */
	}
	(__gfx_state.drawpixel)(x, y, color);
}
#define true 1

void
gfx_init(void (*pixel_func)(int, int, uint32_t), int width, int height)
{
	__gfx_state._width    = width;
	__gfx_state._height   = height;
	__gfx_state.rotation  = 0;
	__gfx_state.cursor_y  = __gfx_state.cursor_x    = 0;
	__gfx_state.textsize  = 1;
	__gfx_state.textcolor = 0;
	__gfx_state.textbgcolor = 0xffffffff;
	__gfx_state.wrap      = true;
	__gfx_state.drawpixel = pixel_func;
}


/* Bresenham's algorithm - thx wikpedia */
void gfx_drawLine(int16_t x0, int16_t y0,
			    int16_t x1, int16_t y1,
			    uint32_t color)
{
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		swap(x0, y0);
		swap(x1, y1);
	}

	if (x0 > x1) {
		swap(x0, x1);
		swap(y0, y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) {
		ystep = 1;
	} else {
		ystep = -1;
	}

	for (; x0 <= x1; x0++) {
		if (steep) {
			gfx_drawPixel(y0, x0, color);
		} else {
			gfx_drawPixel(x0, y0, color);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}

void gfx_drawFastVLine(int16_t x, int16_t y,
		       int16_t h, uint32_t color)
{
	/* Update in subclasses if desired! */
	gfx_drawLine(x, y, x, y + h - 1, color);
}

void gfx_fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
		  uint32_t color)
{
	/* Update in subclasses if desired! */
	int16_t i;
	for (i = x; i < x + w; i++) {
		gfx_drawFastVLine(i, y, h, color);
	}
}

void gfx_fillScreen(uint32_t color)
{
	gfx_fillRect(0, 0, __gfx_state._width, __gfx_state._height, color);
}

void gfx_drawBitmap(int16_t x, int16_t y, tImage bmp)
{
	for (int16_t j = 0; j < bmp.height; j++) {
		for (int16_t i = 0; i < bmp.width; i++) {
				gfx_drawPixel(x + i, y + j, pgm_read_double_word(&bmp.data[j * bmp.width + i])); // ojo con estos indices
			}
		}
}

void gfx_fillCircle(int16_t x0, int16_t y0, int16_t r,
		    uint32_t color)
{
	gfx_drawFastVLine(x0, y0 - r, 2*r+1, color);
	gfx_fillCircleHelper(x0, y0, r, 3, 0, color);
}

/* Used to do circles and roundrects */
void gfx_fillCircleHelper(int16_t x0, int16_t y0, int16_t r,
			  uint8_t cornername, int16_t delta, uint32_t color)
{
	int16_t f     = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x     = 0;
	int16_t y     = r;

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f     += ddF_y;
		}
		x++;
		ddF_x += 2;
		f     += ddF_x;

		if (cornername & 0x1) {
			gfx_drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
			gfx_drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
		}
		if (cornername & 0x2) {
			gfx_drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
			gfx_drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
		}
	}
}


