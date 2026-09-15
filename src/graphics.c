#include "graphics.h"

#include "SDL2/SDL.h"
#include "utils.h"

void fill_rect(
    SDL_Surface* surface,
    RECT rect,
    uint32_t color
){
    if(!surface) return;
    uint32_t* buffer = (uint32_t*)surface->pixels;
    int surface_width = surface->w;
    for(int y=rect.y;y<rect.x+rect.h;y++){
        for(int x=rect.x;x<rect.x+rect.w;x++){
            buffer[y*surface_width+x] = color;
        }
    }
};