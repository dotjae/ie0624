#include "pong.h"

int main(void) {
    clock_setup();
    console_setup(115200);
    sdram_init();
    lcd_spi_init();

    gfx_init(lcd_draw_pixel, LCD_WIDTH,LCD_HEIGHT);
    
    int16_t currentY;
    while (1) {
        gfx_fillScreen(LCD_BLACK);
        gfx_setTextSize(3);
        gfx_setTextColor(LCD_WHITE, LCD_BLACK);
        gfx_puts_centered("&Pong", LCD_HEIGHT * 1/16);  // 38 = '&' -> mu, mapeado en font-7x12.c

        gfx_setTextSize(1);
        currentY = gfx_Y() + 35;
        gfx_puts_centered("Universidad de Costa Rica",      currentY += LINE_HEIGHT);
        gfx_puts_centered("Facultad de Ingenieria",         currentY += LINE_HEIGHT);
        gfx_puts_centered("Escuela de Ingenieria Electrica",currentY += LINE_HEIGHT);
        gfx_puts_centered("IE0624 Laboratorio de",          currentY += LINE_HEIGHT);
        gfx_puts_centered("Microcontroladores, I-2024",     currentY += LINE_HEIGHT);
        gfx_puts_centered("Proyecto de microcontroladores", currentY += LINE_HEIGHT);
        gfx_puts_centered("Profesor:",                      currentY += LINE_HEIGHT);
        gfx_puts_centered("MSc. Marco Villalta F.",         currentY += LINE_HEIGHT);
        gfx_puts_centered("Estudiantes:",                   currentY += LINE_HEIGHT);
        gfx_puts_centered("Jose Flores Q.  B82994",         currentY += LINE_HEIGHT);
        gfx_puts_centered("Roger Piovet G. C15990",         currentY += LINE_HEIGHT);
        lcd_show_frame();
    }
}
