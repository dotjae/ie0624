// tal vez algunos de estos includes no sean necesarios
#include <stdint.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include "clock.h"
#include "console.h"


// Misc
#define WHO_AM_I    0xfh    // identifier reg
#define RNW         0x80    // read reg from gyro

// CTRL regs addresses 
#define CTRL_REG1   0x20
#define CTRL_REG2   0x21
#define CTRL_REG4   0x23
#define CTRL_REG5   0x24

// DATA regs addreses 
#define OUT_TEMP    0x26
#define OUT_X_L     0x28
#define OUT_X_H     0x29
#define OUT_Y_L     0x2A
#define OUT_Y_H     0x2B
#define OUT_Z_L     0x2C
#define OUT_Z_H     0x2D

// CTRL_REG1 bits
#define DR1         (1 << 7)
#define DR0         (1 << 6)
#define BW1         (1 << 5)
#define BW0         (1 << 4)
#define PD          (1 << 3)
#define ZEN         (1 << 2)
#define XEN         (1 << 1)
#define YEN         (1 << 0)

// CTRL_REG4 bits
#define FS_250      0x00     
#define FS_500      0x10
#define FS_2000     0x30

// L3GD20 sensitivity
#define L3GD20_SENSITIVITY_250DPS  (0.00875F)      // Roughly 22/256 for fixed point match
#define L3GD20_SENSITIVITY_500DPS  (0.0175F)       // Roughly 45/256
#define L3GD20_SENSITIVITY_2000DPS (0.070F)        // Roughly 18/256
typedef struct Mems
{
    int16_t x;
    int16_t y;
    int16_t z;
} mems;

void mems_spi_init(void);
uint8_t mems_read_reg(uint8_t reg);
void mems_write_reg(uint8_t reg, uint8_t value);
int8_t mems_temp(void);
int16_t read_axis(uint8_t reg_low, uint8_t reg_high);
mems read_xyz(void);
