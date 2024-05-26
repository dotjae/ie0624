#include "labo4.h"

int main(void)
{
    uint8_t temperature;
    mems reading;

    /* INITS */
	clock_setup();
	console_setup(115200); 
    mems_spi_init();
	sdram_init();
	lcd_spi_init();
    gfx_init(lcd_draw_pixel, 240, 320); 
    
	while (1) 
    {   
        temperature = mems_temp();
        reading = read_xyz();

        lcd_slope(temperature, reading);
	}
}
