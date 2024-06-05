#include "pong.h"

int main(void) {
    clock_setup();
    console_setup(115200);
    sdram_init();
    lcd_spi_init();

    gfx_init(lcd_draw_pixel, LCD_WIDTH,LCD_HEIGHT);
    
    int16_t currentY;
    while (1) {
        gfx_drawBitmap(0,0,image_data_pongMenu,320,240);
        lcd_show_frame();
    }
}
