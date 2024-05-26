#include "labo4.h"

int main(void)
{   
    char str[50];
    uint8_t temperature;

    data xyzData;
    INIT_ANGLE(xyzData.angle);
    INIT_SAMPLE_TIME(xyzData.lastTime);

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
        xyzData.reading = read_xyz();
        xyzData = integrate_xyz(xyzData);
        
        console_puts_angles(xyzData);       
        lcd_slope(temperature, xyzData.reading);
	}
}
