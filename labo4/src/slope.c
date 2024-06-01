#include "labo4.h"

int main(void)
{   
    uint8_t temperature;
    double battery;
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
    adc_setup();
    gfx_init(lcd_draw_pixel, 240, 320);


	while (1) 
    {   
        // Get readings
        temperature = mems_temp();
        xyzData.reading = read_xyz();
        xyzData = integrate_xyz(xyzData);
        battery = get_battery(5); // Use channel 5

        // Setup alert LEDs
        five_degree_alert(xyzData);
        low_battery_alert(battery);

        // Send serial data
        USART_enable = console_usart_enable(xyzData, temperature, battery, USART_enable); 

        // Send serial data
        lcd_slope(temperature, xyzData.angle, battery, USART_enable); 
	}
}
