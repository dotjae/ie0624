#include "fsm.h"

// Inits
uint16_t currentY;
uint16_t cycleEnum          = 0;
uint16_t pressedDuration    = 0;
uint16_t pressedTime        = 0;
uint16_t startTime          = 0;
uint32_t deltaT             = 0;

// FSMs states
gameState STATE = MAIN_MENU;    // Show menu at POR
selState MENU_STATE = SEL_PVP;  // Select PVP at POR
pvpStart PVP_START_STATE = INICIO3; // Show 'Inicio en 3' when PvP is selected
ball_state BALL_STATE = START;

// structs
paddleXY Paddle1;
paddleXY Paddle2;
ballXY Ball;

void menu_fsm(void)
{
    switch (STATE)
    {
        case MAIN_MENU:
            // Title
            gfx_drawBitmap(80,50,pong_outline);
            gfx_drawBitmap(115,57,pong);
            gfx_drawBitmap(86,68,mu);
            
            // Options
            gfx_drawBitmap(117,125,pvp);
            gfx_drawBitmap(113,154,git);
            
            // TODO: function to read button 
            // short press -> toggle between menu options
            // long press  -> access a menu option
            // this should be a fsm
            if (gpio_get(GPIOA,GPIO0))
            {
                pressedTime = mtime();
                
                while (gpio_get(GPIOA,GPIO0)) 
                {
                    pressedDuration = mtime() - pressedTime;   
                }
                
                if (pressedDuration > 1000)
                {
                    STATE = (MENU_STATE == SEL_PVP) ? PVP_INIT: GIT;  // main menu only has pvp and credits options 
                }
                else
                {
                    MENU_STATE = (selState)((cycleEnum += 1) % __count);   // cyclic enum, for menu state transitions
                    milli_sleep(10);
                }
            }

            // Selection
            switch (MENU_STATE)
            {
                case SEL_PVP:
                    gfx_drawBitmap(100,120,options_outline);
                    gfx_drawBitmap(117,125,pvp);
                break;
                case SEL_GIT:
                    gfx_drawBitmap(100,149,options_outline);
                    gfx_drawBitmap(113,154,git);
                break;
                default:
                    MENU_STATE = SEL_PVP;
                break;
            }
        break;

        case PVP_INIT:
            /* paddles start at half screen */
            INIT_PADDLE_Y(Paddle1);       // TODO: generalize for every round taken
            INIT_PADDLE_Y(Paddle2); 
            
            // Title
            gfx_drawBitmap(80,50,pong_outline);
            gfx_drawBitmap(115,57,pong);
            gfx_drawBitmap(86,68,mu);
            
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
