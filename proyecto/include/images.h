#include <stdint.h>

 typedef struct {
     const uint16_t *data;
     uint16_t width;
     uint16_t height;
     uint8_t dataSize;
} tImage;


/* MENU ELEMENTS */

// uPong surrounding rectangle 
extern const tImage outline1;

// Options surrounding rectangle
extern const tImage outline2;

// Main menu strings
extern const tImage strings;

// 'Créditos/Git'
extern const tImage git;

// 'Pong'
extern const tImage pong;

// 'Mu'
extern const tImage mu;

// 'Inicio(PvP)'
extern const tImage pvp;

// QR
extern const tImage qr;

// 'Inicio'
extern const tImage Inicio;

// 1
extern const tImage one;

// 2
extern const tImage two;

// 3
extern const tImage three;

// outline para el inicio
extern const tImage inicio_outline;

// outline para aborts
extern const tImage escape;

// paddle
extern const tImage paddle;

// outline de juego
extern const tImage game_outline;
