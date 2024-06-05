/*
 * This include file describes the functions exported by clock.c
 */

#include <stdint.h>
#include <setjmp.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/iwdg.h>
#include <libopencm3/cm3/scb.h>
#include <libopencm3/cm3/cortex.h>

#ifndef __CLOCK_H
#define __CLOCK_H

/*
 * Definitions for functions being abstracted out
 */
void msleep(uint32_t);
uint32_t mtime(void);
void clock_init(void);

#endif /* generic header protector */

