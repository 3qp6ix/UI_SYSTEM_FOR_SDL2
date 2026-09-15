#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

#include "utils.h"

typedef struct SDL_Surface SDL_Surface;

void fill_rect(
    SDL_Surface* surface,
    RECT rect,
    uint32_t color
);

#endif