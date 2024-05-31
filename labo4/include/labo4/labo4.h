#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "clock.h"
#include "console.h"
#include "sdram.h"
#include "lcd-spi.h"
#include "gfx.h"
#include "mems.h"
#include "button.h"
#include "battery.h"

typedef struct Degree
{
   double x;
   double y;
   double z;
} degree;

typedef struct lastSampleTime
{
    double x;
    double y;
    double z;
} sampleTime;

typedef struct Integration
{
    double angle;
    double lastSampleTime;
} integral;

typedef struct memsData
{
    degree angle;
    sampleTime lastTime;
    mems reading;
} data;

#define SAMPLE_TIME 1
#define INIT_ANGLE(X) do { (X).x = 0; (X).y = 0; (X).z = 0; } while(0)
#define INIT_SAMPLE_TIME(X) do { (X).x = mtime(); (X).y = mtime(); (X).z = mtime(); } while(0)

void lcd_slope(uint8_t temperature, degree reading, double battery, bool USART_enable);

void delay(void);

integral integrate_axis(double reading, double angle, double lastSampleTime);

data integrate_xyz(data xyzData);

bool console_usart_enable(data xyzData, uint8_t temperature, double battery, bool USART_enable);

void console_puts_all(data xyzData, uint8_t temperature, double battery);

void five_degree_alert(data xyzData);
