#include "mems.h"

void mems_spi_init(void)
{   
    // CLKS
	rcc_periph_clock_enable(RCC_SPI5);
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_GPIOF);

    // Chip-select
	gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO1);
    gpio_set(GPIOC, GPIO1);

    // NSS, MISO, MOSI, SCK
	gpio_mode_setup(GPIOF, 
                    GPIO_MODE_AF, 
                    GPIO_PUPD_PULLDOWN,
			        GPIO7 | GPIO8 | GPIO9);
	gpio_set_af(GPIOF, 
                GPIO_AF5, 
                GPIO7 | GPIO8 | GPIO9);


    // SPI-Init
    spi_set_master_mode(SPI5);
    spi_set_baudrate_prescaler(SPI5, SPI_CR1_BR_FPCLK_DIV_64);
    spi_set_clock_polarity_0(SPI5);
    spi_set_clock_phase_0(SPI5);
    spi_set_full_duplex_mode(SPI5);
    spi_set_unidirectional_mode(SPI5);
    spi_enable_software_slave_management(SPI5);
    spi_send_msb_first(SPI5);
    spi_set_nss_high(SPI5);
    SPI_I2SCFGR(SPI5) &= ~SPI_I2SCFGR_I2SMOD;
    spi_enable(SPI5);

    // Inicialización de registros
    mems_write_reg(CTRL_REG1, 0x4f);
    //mems_write_reg(CTRL_REG1, BW1 | BW0 | PD | ZEN | XEN | YEN);
    mems_write_reg(CTRL_REG4, FS_250);
}


uint8_t mems_read_reg(uint8_t reg)
{
    uint8_t result;

    gpio_clear(GPIOC, GPIO1);     
    spi_send(SPI5, RNW | reg);       
    spi_read(SPI5);                 
    spi_send(SPI5, 0);               
    result = spi_read(SPI5);  
    gpio_set(GPIOC, GPIO1);            
    return result;                     
}

void mems_write_reg(uint8_t reg, uint8_t value)
{
    gpio_clear(GPIOC, GPIO1);
    spi_send(SPI5, reg);
    spi_read(SPI5);
    spi_send(SPI5, value);
    spi_read(SPI5);
    gpio_set(GPIOC, GPIO1);    
}

int8_t mems_temp(void)
{
    return mems_read_reg(OUT_TEMP);
}

int16_t read_axis(uint8_t reg_low, uint8_t reg_high) 
{
    int16_t axis;
    axis = mems_read_reg(reg_low);              
    axis |= mems_read_reg(reg_high) << 8;
    return axis;                                       
}

mems read_xyz(void) {
    mems reading;
    
    reading.x = (read_axis(OUT_X_L | RNW, OUT_X_H | RNW) * L3GD20_SENSITIVITY_250DPS) + 5;
    reading.y = (read_axis(OUT_Y_L | RNW, OUT_Y_H | RNW) * L3GD20_SENSITIVITY_250DPS) - 17;
    reading.z = (read_axis(OUT_Z_L | RNW, OUT_Z_H | RNW) * L3GD20_SENSITIVITY_250DPS) + 17;

    return reading;
}
