#include "labo4.h"

int main(void)
{
    uint8_t tmp;
    char str[128];
    
    /* INITS */
	clock_setup();
	console_setup(115200); 
    mems_spi_init();
	sdram_init();
	lcd_spi_init();
    gfx_init(lcd_draw_pixel, 240, 320); 
    
    // Check WHO_AM_I
    tmp = mems_read_reg(0xf);
    sprintf(str, "%4x\n", tmp);
    
	while (1) 
    {   
        console_puts("WHO_AM_I: ");
        console_puts(str);
        console_puts("\n");
        delay();

        lcd_pendientes();
	}
}
