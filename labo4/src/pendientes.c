#include "labo4.h"

int main(void)
{   
    // inicialización
	clock_setup();
	console_setup(115200); 
	sdram_init();
	lcd_spi_init();
	gfx_init(lcd_draw_pixel, 240, 320); 

	while (1) 
    {
        lcd_pendientes();
	}
}
