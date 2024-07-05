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
    PVM_INIT,
    PVM,
    PVP,
    GIT
} gameState;

// TODO: change this enum name to a more apropiate one 
// Sub-state definitions
typedef enum
{
    SEL_PVP,
    SEL_PVM,
    SEL_GIT
} selState;

// PVP countdown states
typedef enum
{
    INICIO3,
    INICIO2,
    INICIO1
} pvpStart;

// PVM countdown states
typedef enum
{
    INICIO3M,
    INICIO2M,
    INICIO1M
} pvmStart; 

// for pong logic
typedef struct
{
    uint16_t x,y;
    uint16_t height;
    uint8_t score;
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
    WINNER,
} ball_state;

// long-short press states
typedef enum
{
    NOT_PRESS,
    SHORT_PRESS,
    LONG_PRESS,
} press_state;

// git menu states
typedef enum
{
    LOGOS,
    GIT_QR,
} git_state;

#define INIT_PADDLE_Y(paddle) do{(paddle).y = 90;(paddle).score = 0;} while(0)  // TODO: generalize for any paddle height
#define MOV_PADDLE 5   // pixels paddle moves while button is actioned
#define LINE_HEIGHT 20

// function definitions
void menu_fsm(void);
void ball_update(void);
uint8_t dumb_agent(uint16_t paddle_y, int16_t ball_y);
dir ball_Dir(void);
int long_press(void);
void draw_game_division(void);

#endif
