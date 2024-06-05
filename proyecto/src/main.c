#include "pong.h"


int main(void) {
    clock_init  ();
    console_init(115200);
    button_init ();
    sdram_init  ();
    lcd_spi_init();
    gfx_init    (lcd_draw_pixel, LCD_WIDTH,LCD_HEIGHT);
    
    while (1) {
        menu_fsm();       
        lcd_show_frame();
    }
}
