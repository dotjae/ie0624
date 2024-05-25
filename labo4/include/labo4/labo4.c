#include "labo4.h"

void lcd_slope(uint8_t temperature)
{
    char buf[4];

    // interface
    gfx_fillScreen(LCD_BLACK);
    gfx_fillRoundRect(10, 10, 220, 220, 5, LCD_WHITE);
    gfx_drawRoundRect(10, 10, 220, 220, 5, LCD_RED);
    gfx_fillCircle(20, 250, 10, LCD_RED);
    gfx_fillCircle(120, 250, 10, LCD_GREEN);
    gfx_fillCircle(220, 250, 10, LCD_BLUE);
    
    // Title
    gfx_setTextSize(2);
    gfx_setCursor(35, 25);
    gfx_puts("MONITOR DE");
    gfx_setCursor(35, 50);
    gfx_puts("PENDIENTES");

    // XYZ axis, temperature, battery level
    gfx_setTextSize(1);
    gfx_setCursor(15, 100);
    gfx_puts("BATERIA: 00%");

    gfx_setCursor(15, 115);
    gfx_puts("TEMPERATURA: ");
    gfx_setCursor(105, 115);
    sprintf(buf, "%3d", temperature);
    gfx_puts(buf);

    gfx_setCursor(15, 130);
    gfx_puts("EJE X: 000");
    gfx_setCursor(15, 145);
    gfx_puts("EJE Y: 000");
    gfx_setCursor(15, 160);
    gfx_puts("EJE Z: 000");
    gfx_setCursor(15, 175);
    gfx_puts("COMM SERIAL: OFF");
    
    // Update screen
    lcd_show_frame();   
}

void delay(void)
{
    for (int i = 0; i < 6000000; i++) __asm__ ( "nop" );
}
