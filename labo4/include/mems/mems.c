#include "mems.h"

/**
 * @brief Initializes the SPI interface for the MEMS sensor.
 *
 * This function sets up the necessary clocks, GPIO pins, and SPI settings to communicate with the MEMS sensor. It also initializes the control registers of the MEMS sensor.
 *
 * @param void This function does not take any parameters.
 * @return void This function does not return any values.
 */
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

/**
 * @brief Reads a register from the MEMS sensor.
 *
 * This function reads and returns the value of a specified register from the MEMS sensor using SPI communication.
 *
 * @param reg The address of the register to read.
 * @return uint8_t The value read from the specified register.
 */
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

/**
 * @brief Writes a value to a register of the MEMS sensor.
 *
 * This function writes a specified value to a register of the MEMS sensor using SPI communication.
 *
 * @param reg The address of the register to write to.
 * @param value The value to write to the register.
 * @return void This function does not return any values.
 */
void mems_write_reg(uint8_t reg, uint8_t value)
{
    gpio_clear(GPIOC, GPIO1);
    spi_send(SPI5, reg);
    spi_read(SPI5);
    spi_send(SPI5, value);
    spi_read(SPI5);
    gpio_set(GPIOC, GPIO1);    
}

/**
 * @brief Reads the temperature from the MEMS sensor.
 *
 * This function reads and returns the temperature value from the MEMS sensor.
 *
 * @param void This function does not take any parameters.
 * @return int8_t The temperature value read from the MEMS sensor.
 */
int8_t mems_temp(void)
{
    return mems_read_reg(OUT_TEMP);
}

/**
 * @brief Reads an axis value from the MEMS sensor.
 *
 * This function reads and combines the low and high byte values of a specified axis from the MEMS sensor.
 *
 * @param reg_low The address of the low byte register of the axis.
 * @param reg_high The address of the high byte register of the axis.
 * @return int16_t The combined axis value.
 */
int16_t read_axis(uint8_t reg_low, uint8_t reg_high) 
{
    int16_t axis;
    axis = mems_read_reg(reg_low);              
    axis |= mems_read_reg(reg_high) << 8;
    return axis;                                       
}

/**
 * @brief Reads the XYZ axis values from the MEMS sensor.
 *
 * This function reads and returns the XYZ axis values from the MEMS sensor.
 *
 * @param void This function does not take any parameters.
 * @return mems A struct containing the XYZ axis values.
 */
mems read_xyz(void) {
    mems reading;
    
    reading.x = (read_axis(OUT_X_L | RNW, OUT_X_H | RNW) * L3GD20_SENSITIVITY_250DPS);
    reading.y = (read_axis(OUT_Y_L | RNW, OUT_Y_H | RNW) * L3GD20_SENSITIVITY_250DPS);
    reading.z = (read_axis(OUT_Z_L | RNW, OUT_Z_H | RNW) * L3GD20_SENSITIVITY_250DPS);

    return reading;
}
