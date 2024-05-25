#include "labo4.h"

void lcd_pendientes(void)
{
    // interfaz
    gfx_fillScreen(LCD_BLACK);
    gfx_fillRoundRect(10, 10, 220, 220, 5, LCD_WHITE);
    gfx_drawRoundRect(10, 10, 220, 220, 5, LCD_RED);
    gfx_fillCircle(20, 250, 10, LCD_RED);
    gfx_fillCircle(120, 250, 10, LCD_GREEN);
    gfx_fillCircle(220, 250, 10, LCD_BLUE);
    
    // Título
    gfx_setTextSize(2);
    gfx_setCursor(35, 25);
    gfx_puts("MONITOR DE");
    gfx_setCursor(35, 50);
    gfx_puts("PENDIENTES");

    // Ejes XYZ, temperatura, batería 
    gfx_setTextSize(1);
    gfx_setCursor(15, 100);
    gfx_puts("BATERIA: 00%");
    gfx_setCursor(15, 115);
    gfx_puts("TEMPERATURA: 25 Celsius");
    gfx_setCursor(15, 130);
    gfx_puts("EJE X: 000");
    gfx_setCursor(15, 145);
    gfx_puts("EJE Y: 000");
    gfx_setCursor(15, 160);
    gfx_puts("EJE Z: 000");
    gfx_setCursor(15, 175);
    gfx_puts("COMM SERIAL: OFF");

    lcd_show_frame();   // actualizar pantalla 
}
