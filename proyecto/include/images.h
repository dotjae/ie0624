#ifndef __IMAGES_H
#define __IMAGES_H

#include <stdint.h>



typedef struct {
     const uint8_t *data;
     uint16_t width;
     uint16_t height;
     uint8_t dataSize;
} tImage;

extern const tImage logos;
extern const tImage qr;

#endif 
