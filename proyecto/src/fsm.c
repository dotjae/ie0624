#include "fsm.h"
// <<<<<<< HEAD
#include <stdbool.h>

// FSMs states
gameState STATE = MAIN_MENU;            // Show menu at POR
selState MENU_STATE = SEL_PVP;          // Select PVP at POR
pvpStart PVP_START_STATE = INICIO3;     // Show 'Inicio en 3' when PvP is selected
pvmStart PVM_START_STATE = INICIO3M;    // Show 'Inicio en 3' when PvP is selected
ball_state BALL_STATE = START;
press_state PRESS_STATE = NOT_PRESS;    // for button press timing
// =======
// >>>>>>> 6f0a411e868b1ce56e7eab600fc88595ccbf73ec

// Inits
uint16_t currentY;
uint32_t startTime          = 0;
uint32_t deltaT             = 0;
uint8_t agent_decision;

// FSMs states
// gameState STATE = MAIN_MENU;    // Show menu at POR
// selState MENU_STATE = SEL_PVP;  // Select PVP at POR
// pvpStart PVP_START_STATE = INICIO3; // Show 'Inicio en 3' when PvP is selected
// ball_state BALL_STATE = START;

// structs
paddleXY Paddle1;
paddleXY Paddle2;
ballXY Ball;

void menu_fsm(void)
{
    gfx_setTextColor(GFX_WHITE,GFX_BLACK);
    switch (STATE)
    {
        case MAIN_MENU:
            // Title
            gfx_box(80,50,170,50,4,1);
            gfx_setCursor(86,57);
            gfx_setTextSize(4); 
            gfx_puts("~Pong");
            
            // Options
            gfx_setTextSize(1); 

            gfx_setCursor(113,125);
            gfx_puts("Modo PvP");

            gfx_setCursor(113,150);
            gfx_puts("Modo PvM");

            gfx_setCursor(113,175);
            gfx_puts("Creditos/Git");
            

            // Selection
            switch (MENU_STATE)
            {
                case SEL_PVP:
                    gfx_box(100,120,120,20,4,1);
                    gfx_setCursor(117,125);
                    gfx_puts("Modo PvP");
                    
                    switch (PRESS_STATE)
                    {
                        case NOT_PRESS:
                            PRESS_STATE = long_press();
                        break;
                        case SHORT_PRESS:
                            MENU_STATE = SEL_PVM;
                            PRESS_STATE = NOT_PRESS;
                            milli_sleep(10);
                        break;
                        case LONG_PRESS:
                            STATE = PVP_INIT;
                            PRESS_STATE = NOT_PRESS;
                        break;
                    }
                break;
                case SEL_PVM:
                    gfx_box(100,145,120,20,4,1);
                    gfx_setCursor(117,150);
                    gfx_puts("Modo PvM");
                    
                    switch (PRESS_STATE)
                    {
                        case NOT_PRESS:
                            PRESS_STATE = long_press();
                        break;
                        case SHORT_PRESS:
                            MENU_STATE = SEL_GIT;
                            PRESS_STATE = NOT_PRESS;
                            milli_sleep(10);
                        break;
                        case LONG_PRESS:
                            STATE = PVM_INIT;
                            PRESS_STATE = NOT_PRESS;
                        break;
                    }
                break;
                case SEL_GIT:
                    gfx_box(100,170,120,20,4,1);
                    gfx_setCursor(117,175);
                    gfx_puts("Creditos/Git");

                    switch (PRESS_STATE)
                    {
                        case NOT_PRESS:
                            PRESS_STATE = long_press();
                        break;
                        case SHORT_PRESS:
                            MENU_STATE = SEL_PVP;
                            PRESS_STATE = NOT_PRESS;
                            milli_sleep(10);
                        break;
                        case LONG_PRESS:
                            STATE = GIT;
                            PRESS_STATE = NOT_PRESS;
                        break;
                    }

                break;
            }
        break;

        case PVP_INIT:
            /* paddles start at half screen */
            INIT_PADDLE_Y(Paddle1);       // TODO: generalize for every round taken
            INIT_PADDLE_Y(Paddle2); 
            
            // Title
            gfx_box(80,50,170,50,4,1);
            gfx_setCursor(86,57);
            gfx_setTextSize(4); 
            gfx_puts("~Pong");
            
            // 'Inicio en 3,2,1...'
            gfx_drawBitmap(90,120,inicio_outline);
            gfx_drawBitmap(104,135,Inicio);
            
            // 'Presione un botón para cancelar'
            gfx_drawBitmap(89,191,escape);
                
            // TODO: after sometime a POR is done, startTime does not default to 0
            switch (PVP_START_STATE)
            {
                case INICIO3:
                    gfx_drawBitmap(208,136,three);
                    if (startTime == 0)
                    {
                        startTime = mtime();
                    }
                    if (mtime() - startTime > 1000)
                    {
                       PVP_START_STATE = INICIO2; 
                    }
                break;
                case INICIO2:
                    gfx_drawBitmap(208,136,two);
                    if (mtime() - startTime > 2000)
                    {
                       PVP_START_STATE = INICIO1; 
                    }
                break;
                case INICIO1:
                    gfx_drawBitmap(208,136,one);
                    if (mtime() - startTime > 3000)
                    {
                       startTime = 0;
                       PVP_START_STATE = INICIO3; 
                       STATE = PVP;
                    }
                break;
            }
            
            // poll interrupt on button -> abort pvp 
            if (gpio_get(GPIOA,GPIO0))
            {
                startTime = 0;
                PVP_START_STATE = INICIO3; 
                STATE = MAIN_MENU;
            }
            break;
            case PVM_INIT:
            /* paddles start at half screen */
            INIT_PADDLE_Y(Paddle1);       // TODO: generalize for every round taken
            INIT_PADDLE_Y(Paddle2); 
            
            // Title
            gfx_box(80,50,170,50,4,1);
            gfx_setCursor(86,57);
            gfx_setTextSize(4); 
            gfx_puts("~Pong");

            // 'Inicio en 3,2,1...'
            gfx_drawBitmap(90,120,inicio_outline);
            gfx_drawBitmap(104,135,Inicio);
            
            // 'Presione un botón para cancelar'
            gfx_drawBitmap(89,191,escape);
                
            // TODO: after sometime a POR is done, startTime does not default to 0
            switch (PVM_START_STATE)
            {
                case INICIO3M:
                    gfx_drawBitmap(208,136,three);
                    if (startTime == 0)
                    {
                        startTime = mtime();
                    }
                    if (mtime() - startTime > 1000)
                    {
                       PVM_START_STATE = INICIO2M; 
                    }
                break;
                case INICIO2M:
                    gfx_drawBitmap(208,136,two);
                    if (mtime() - startTime > 2000)
                    {
                       PVM_START_STATE = INICIO1M; 
                    }
                break;
                case INICIO1M:
                    gfx_drawBitmap(208,136,one);
                    if (mtime() - startTime > 3000)
                    {
                       startTime = 0;
                       PVM_START_STATE = INICIO3M; 
                       STATE = PVM;
                    }
                break;
            }
            
            // poll interrupt on button -> abort pvp 
            if (gpio_get(GPIOA,GPIO0))
            {
                startTime = 0;
                PVM_START_STATE = INICIO3M; 
                STATE = MAIN_MENU;
            }
            break;
        case PVP:
            /* left paddle */
            // move paddle down
            if (gpio_get(GPIOA,GPIO1))
            {
                Paddle1.y += MOV_PADDLE;
                gpio_toggle(GPIOG,GPIO13);
            }

            // move paddle up
            if (gpio_get(GPIOA,GPIO0))
            {
                Paddle1.y -= MOV_PADDLE;
                gpio_toggle(GPIOG,GPIO14);
            }
            
            if (Paddle1.y >= 165) Paddle1.y = 165;
            if (Paddle1.y <= 15 ) Paddle1.y = 15;

            gfx_fillRect(15,Paddle1.y,10,60,GFX_WHITE);

            /* right paddle */
            // move paddle down
            if (gpio_get(GPIOA,GPIO7) && Paddle2.y <= 165)
            {
                Paddle2.y += MOV_PADDLE;
                gpio_toggle(GPIOG,GPIO13);
            }

            // move paddle up
            if (gpio_get(GPIOA,GPIO5) && Paddle2.y > 15)
            {
                Paddle2.y -= MOV_PADDLE;
                gpio_toggle(GPIOG,GPIO14);
            }

            if (Paddle2.y >= 165) Paddle2.y = 165;
            if (Paddle2.y <= 15 ) Paddle2.y = 15;

            gfx_fillRect(295,Paddle2.y,10,60,GFX_WHITE);
            
            /* ball */
            switch (BALL_STATE)
            {
                case START:
                    Ball.x = 160;
                    Ball.y = 120;
                    
                    Ball.Dir = ball_Dir();

                    // Randomize x and y velocities via randDirX randDirY
                    Ball.dx = 5 * Ball.Dir.x;
                    Ball.dy = 5 * Ball.Dir.y;

                    gfx_fillCircle(Ball.x, Ball.y, 5, GFX_WHITE);
                    BALL_STATE = FLOATING;
                break;

                case FLOATING:
                    ball_update();
                    if (Ball.y >= 235 || Ball.y <= 5)
                        BALL_STATE = HORIZONTAL;
                    else if (Ball.x <= 25 || Ball.x >= 295 )
                    {
                        if ((Ball.x <= 25 && (Ball.y >= Paddle1.y && Ball.y <= Paddle1.y + 60)) || (Ball.x >= 295 && (Ball.y >= Paddle2.y && Ball.y <= Paddle2.y + 60)))
                            BALL_STATE = SAVE;
                        else 
                            BALL_STATE = GOAL;
                    }
                    else 
                        BALL_STATE = FLOATING;
                break;
                case SAVE:
                    Ball.dx = -Ball.dx;
                    ball_update();
                    BALL_STATE = FLOATING;
                break;
                case GOAL:
                    ball_update();
                    if (Ball.x <= -10 || Ball.x >= 330)
                        BALL_STATE = START;
                break;
                case HORIZONTAL:
                    Ball.dy = -Ball.dy;
                    ball_update();
                    BALL_STATE = FLOATING;
                break;
            }
        break;
        case PVM:

            // gfx_drawBitmap(10,10,game_outline);
            
            /* left paddle */
            // move paddle down
            if (gpio_get(GPIOA,GPIO1))
            {
                Paddle1.y += MOV_PADDLE;
                gpio_toggle(GPIOG,GPIO13);
            }

            // move paddle up
            if (gpio_get(GPIOA,GPIO0))
            {
                Paddle1.y -= MOV_PADDLE;
                gpio_toggle(GPIOG,GPIO14);
            }
            
            if (Paddle1.y >= 165) Paddle1.y = 165;
            if (Paddle1.y <= 15 ) Paddle1.y = 15;

            gfx_fillRect(15,Paddle1.y,10,60,GFX_WHITE);

            /* right paddle */
            // move paddle down
            // if (gpio_get(GPIOA,GPIO7) && Paddle2.y <= 165)
            // {
            //     Paddle2.y += MOV_PADDLE;
            //     gpio_toggle(GPIOG,GPIO13);
            // }

            // // move paddle up
            // if (gpio_get(GPIOA,GPIO5) && Paddle2.y > 15)
            // {
            //     Paddle2.y -= MOV_PADDLE;
            //     gpio_toggle(GPIOG,GPIO14);
            // }

            // Hard-coded "dumb" agent to test.
            agent_decision = dumb_agent(Ball.x, Ball.y, Ball.dx, Ball.dy);

            switch (agent_decision)
            {
            case (0):
                Paddle2.y += MOV_PADDLE;
            break;
            case (1):
                Paddle2.y -= MOV_PADDLE;   
                break;
            default:
                Paddle2.y = Paddle2.y;
                break;
            }

            if (Paddle2.y >= 165) Paddle2.y = 165;
            if (Paddle2.y <= 15 ) Paddle2.y = 15;

            gfx_fillRect(295,Paddle2.y,10,60,GFX_WHITE);
            
            /* ball */
            switch (BALL_STATE)
            {
                case START:
                    Ball.x = 160;
                    Ball.y = 120;
                    Ball.dx = 5;
                    Ball.dy = 5;

                    gfx_fillCircle(Ball.x, Ball.y, 5, GFX_WHITE);
                    BALL_STATE = FLOATING;
                break;

                // else if ((Ball.x <= 25 && (Ball.y >= Paddle1.y && Ball.y <= Paddle1.y + 60)) || (Ball.x >= 295 && (Ball.y >= Paddle2.y && Ball.y <= Paddle2.y + 60)))

                case FLOATING:
                    ball_update();
                    // BALL_STATE = (Ball.y >= 235 || Ball.y <= 5) ? HORIZONTAL: ( (Ball.x <= 5 || Ball.x >= 315) ? SAVE : FLOATING);
                    if (Ball.y >= 235 || Ball.y <= 5)
                        BALL_STATE = HORIZONTAL;
                    else if (Ball.x <= 25 || Ball.x >= 295 )
                    {
                        if ((Ball.x <= 25 && (Ball.y >= Paddle1.y && Ball.y <= Paddle1.y + 60)) || (Ball.x >= 295 && (Ball.y >= Paddle2.y && Ball.y <= Paddle2.y + 60)))
                            BALL_STATE = SAVE;
                        else 
                            BALL_STATE = GOAL;
                    }
                    else 
                        BALL_STATE = FLOATING;
                break;
                case SAVE:
                    Ball.dx = -Ball.dx;
                    ball_update();
                    BALL_STATE = FLOATING;
                break;
                case GOAL:
                    ball_update();
                    if (Ball.x <= -10 || Ball.x >= 330)
                        BALL_STATE = START;
                break;
                case HORIZONTAL:
                    Ball.dy = -Ball.dy;
                    ball_update();
                    BALL_STATE = FLOATING;
                break;
            }
        break;
        case GIT:
            // WIP
             milli_sleep(10000);
            STATE = MAIN_MENU;
        break;
    }
}

void ball_update()
{
    Ball.x += Ball.dx;
    Ball.y += Ball.dy;
    gfx_fillCircle(Ball.x, Ball.y, 5, GFX_WHITE);
}

// <<<<<<< HEAD

uint8_t dumb_agent(int16_t x, int16_t y, int16_t dx, int16_t dy)
{

    if (dy < 0) 
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}
// =======
dir ball_Dir(void)
{
    dir Dir;
    int16_t dirX = random_int() % 2;
    int16_t dirY = random_int() % 2;

    if (dirX == 0) 
        dirX = -1;
    else 
        dirX = 1;

    if (dirY == 0) 
        dirY = -1;
    else 
        dirY = 1;
    
    Dir.x = dirX;
    Dir.y = dirY;

    return Dir;
}
// >>>>>>> 6f0a411e868b1ce56e7eab600fc88595ccbf73ec


int long_press(void)
{
    uint32_t pressedTime = 0, pressedDuration = 0;
    if (gpio_get(GPIOA,GPIO0))
    {
        pressedTime = mtime();
    
        while (gpio_get(GPIOA,GPIO0)) 
            pressedDuration = mtime() - pressedTime;   
    
        if (pressedDuration > 1000)
            return LONG_PRESS;
        else 
            return SHORT_PRESS;
    }
    return NOT_PRESS;
}
