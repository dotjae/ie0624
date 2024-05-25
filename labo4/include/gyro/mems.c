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
    mems_write_reg( GYR_CTRL_REG1, 
                    GYR_CTRL_REG1_PD  | 
                    GYR_CTRL_REG1_XEN | 
                    GYR_CTRL_REG1_YEN | 
                    GYR_CTRL_REG1_ZEN | 
                    (3 << GYR_CTRL_REG1_BW_SHIFT));
    
    mems_write_reg( GYR_CTRL_REG4,
                    (1 << GYR_CTRL_REG4_FS_SHIFT));
}


uint8_t mems_read_reg(uint8_t reg)
{
    uint8_t result;

    gpio_clear(GPIOC, GPIO1);     
    spi_send(SPI5, 0x80 | reg);       
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
