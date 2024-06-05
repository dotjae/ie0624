#include "fsm.h"

// Global state definitions
typedef enum
{
    MAIN_MENU,
    PVP,
    GIT
} gameState;

// Sub-state definitions
typedef enum
{
    SEL_PVP,
    SEL_GIT,
    __count
} selState;

gameState STATE = MAIN_MENU;    // Show menu at POR
selState MENU_STATE = SEL_PVP;  // Select PVP at POR

uint16_t currentY;
uint16_t cycleEnum          = 0;
uint16_t pressedDuration    = 0;
uint32_t pressedTime        = 0;

void menu_fsm(void)
{
    switch (STATE)
    {
        case MAIN_MENU:
            gfx_fillScreen(LCD_BLACK);
            // Title
            gfx_drawBitmap(80,50,outline1.data,outline1.width,outline1.height);
            gfx_drawBitmap(115,57,pong.data,pong.width,pong.height);
            gfx_drawBitmap(86,68,mu.data,mu.width,mu.height);
            
            // Options
            gfx_drawBitmap(117,125,pvp.data,pvp.width,pvp.height);
            gfx_drawBitmap(113,154,git.data,git.width,git.height);
            
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
                    STATE = (MENU_STATE == SEL_PVP) ? PVP: GIT;
                }
                else
                {
                    MENU_STATE = (selState)((cycleEnum += 1) % __count);   // cyclic enum, for menu state transitions
                    msleep(10);
                }
            }

            // Selection
            switch (MENU_STATE)
            {
                case SEL_PVP:
                    gfx_drawBitmap(100,120,outline2.data,outline2.width,outline2.height);
                    gfx_drawBitmap(117,125,pvp.data,pvp.width,pvp.height);
                break;
                case SEL_GIT:
                    gfx_drawBitmap(100,149,outline2.data,outline2.width,outline2.height);
                    gfx_drawBitmap(113,154,git.data,git.width,git.height);
                break;
                default:
                    MENU_STATE = SEL_PVP;
                break;
            }
        break;
        case PVP:
            gfx_fillScreen(LCD_BLACK);
            gfx_setTextSize(4);
            gfx_setTextColor(LCD_WHITE,LCD_BLACK);
            gfx_puts_centered("WIP", LCD_HEIGHT/2);
            lcd_show_frame();
            msleep(3000);
            STATE = MAIN_MENU;
        break;
        case GIT:
            gfx_fillScreen(LCD_BLACK);
            gfx_setTextSize(1);
            gfx_setTextColor(LCD_WHITE,LCD_BLACK);
            currentY = 0;
            gfx_puts_centered("Universidad de Costa Rica",      currentY += LINE_HEIGHT);
            gfx_puts_centered("Facultad de Ingenieria",         currentY += LINE_HEIGHT);
            gfx_puts_centered("Escuela de Ingenieria Electrica",currentY += LINE_HEIGHT);
            gfx_puts_centered("IE0624 Laboratorio de",          currentY += LINE_HEIGHT);
            gfx_puts_centered("Microcontroladores, I-2024",     currentY += LINE_HEIGHT);
            gfx_puts_centered("Proyecto de microcontroladores", currentY += LINE_HEIGHT);
            gfx_puts_centered("Profesor:",                      currentY += LINE_HEIGHT);
            gfx_puts_centered("MSc. Marco Villalta F.",         currentY += LINE_HEIGHT);
            gfx_puts_centered("Estudiantes:",                   currentY += LINE_HEIGHT);
            gfx_puts_centered("Jose Flores Q.  B82994",         currentY += LINE_HEIGHT);
            gfx_puts_centered("Roger Piovet G. C15990",         currentY += LINE_HEIGHT);
            lcd_show_frame();
            msleep(10000);
            gfx_drawBitmap(0,0,qr.data,qr.width,qr.height);
            lcd_show_frame();
            msleep(10000);
            STATE = MAIN_MENU;
        break;
    }
}
