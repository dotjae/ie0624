#ifndef __RNG_H
#define __RNG_H

#include <libopencm3/cm3/common.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/f4/rng.h>

void rng_setup(void);
uint32_t random_int(void);

#endif 
