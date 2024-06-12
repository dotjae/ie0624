#ifndef __IMAGES_H
#define __IMAGES_H

#include <stdint.h>



typedef struct {
     const uint32_t *data;
     uint16_t width;
     uint16_t height;
     uint8_t dataSize;
} tImage;


/* MENU ELEMENTS */
// Abort for game load
extern const tImage escape;

// game outline
extern const tImage game_outline;

// 'Créditos/Git'
extern const tImage git;

// 'Inicio'
extern const tImage Inicio;

// Outline for countdown
extern const tImage inicio_outline;

// 'mu'
extern const tImage mu;

// 1
extern const tImage one;

// 2
extern const tImage two;

// 3
extern const tImage three;

// Options outline
extern const tImage options_outline;

// Paddle
extern const tImage paddle;

// 'Pong'
extern const tImage pong;

// Pong outline
extern const tImage pong_outline;

// 'Inicio(PvP)'
extern const tImage pvp;

// Main menu strings
extern const tImage strings;

#endif 
