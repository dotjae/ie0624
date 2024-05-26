#include "labo4.h"

int main(void)
{   
    uint8_t temperature;
    bool USART_enable = true;

    data xyzData;
    INIT_ANGLE(xyzData.angle);
    INIT_SAMPLE_TIME(xyzData.lastTime);

    /* INITS */
	clock_setup();
	console_setup(115200); 
    mems_spi_init();
	sdram_init();
	lcd_spi_init();
    button_setup();
    gfx_init(lcd_draw_pixel, 240, 320); 

	while (1) 
    {   
        temperature = mems_temp();
        xyzData.reading = read_xyz();
        xyzData = integrate_xyz(xyzData);

        five_degree_alert(xyzData);
        USART_enable = console_usart_enable(xyzData, USART_enable);
        lcd_slope(temperature, xyzData.reading, USART_enable);
	}
}
