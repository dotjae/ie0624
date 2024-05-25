// tal vez algunos de estos includes no sean necesarios
#include <stdint.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include "clock.h"
#include "console.h"

// Registros
#define GYR_WHO_AM_I		0x0F
#define GYR_OUT_TEMP		0x26
#define GYR_STATUS_REG		0x27
#define GYR_CTRL_REG1		0x20
#define GYR_CTRL_REG4		0x23
#define GYR_OUT_X_L		    0x28
#define GYR_OUT_X_H		    0x29
#define GYR_OUT_Y_L		    0x2A
#define GYR_OUT_Y_H		    0x2B
#define GYR_OUT_Z_L		    0x2C
#define GYR_OUT_Z_H		    0x2D
#define GYR_OUT_TEMP        0x26

// Bits
#define GYR_RNW			        (1 << 7) 
#define GYR_MNS			        (1 << 6) 
#define GYR_CTRL_REG1_PD	    (1 << 3)
#define GYR_CTRL_REG1_XEN	    (1 << 1)
#define GYR_CTRL_REG1_YEN	    (1 << 0)
#define GYR_CTRL_REG1_ZEN	    (1 << 2)
#define GYR_CTRL_REG1_BW_SHIFT	4
#define GYR_CTRL_REG4_FS_SHIFT	4

// Sensibilidad
#define L3GD20_SENSITIVITY_250DPS  (0.00875F)      
#define L3GD20_SENSITIVITY_500DPS  (0.0175F)      
#define L3GD20_SENSITIVITY_2000DPS (0.070F)      
#define L3GD20_DPS_TO_RADS         (0.017453293F) 


void mems_spi_init(void);
uint8_t mems_read_reg(uint8_t reg);
void mems_write_reg(uint8_t reg, uint8_t value);
uint8_t mems_temp(void);
