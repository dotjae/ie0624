#ifndef __FSM_H
#define __FSM_H

#include <stdint.h>
#include <stdbool.h>
#include <libopencm3/stm32/gpio.h>
#include "clock.h"
#include "random.h"
#include "lcd-spi.h"
#include "gfx.h"
#include "images.h"

// Global state definitions
typedef enum
{
    MAIN_MENU,
    PVP_INIT,
    PVP,
    GIT
} gameState;

// TODO: change this enum name to a more apropiate one 
// Sub-state definitions
typedef enum
{
    SEL_PVP,
    SEL_GIT,
    __count
} selState;

// PVP countdown states
typedef enum
{
    INICIO3,
    INICIO2,
    INICIO1
} pvpStart; 

// for pong logic
typedef struct
{
    uint16_t x,y;
    uint16_t height;
} paddleXY;

// for ball movement

typedef struct
{
    int16_t x, y;
} dir;

typedef struct
{   
    int16_t x,y;
    int16_t dx,dy;   
    dir Dir;
} ballXY;

// ball states
typedef enum
{
    START,
    FLOATING,
    SAVE,
    GOAL,
    HORIZONTAL,
} ball_state;

#define INIT_PADDLE_Y(paddle) do{(paddle).y = 90;} while(0)  // TODO: generalize for any paddle height
#define MOV_PADDLE 5   // pixels paddle moves while button is actioned
#define LINE_HEIGHT 20

// function definitions
void menu_fsm(void);
void ball_update(void);
dir ball_Dir(void);

#endif
