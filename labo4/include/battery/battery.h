#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dac.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>



void adc_setup(void);
uint16_t read_adc_naiive(uint8_t channel);
double get_battery(uint8_t channel);
void low_battery_alert(double battery);
