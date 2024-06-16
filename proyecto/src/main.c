#include "pong.h" 

int main(void)
{
	/* init timers. */
	clock_setup();

	/* set up USART 1. */
	console_setup(115200);
	console_stdio_setup();
    
	/* set up SDRAM. */
	sdram_init();

	lcd_dma_init();
	lcd_spi_init();
    button_init();

    gfx_init(draw_pixel, 320, 240);

	while (1) {
        gfx_fillScreen(GFX_BLACK);
        menu_fsm();
        show_frame();
    }

}
