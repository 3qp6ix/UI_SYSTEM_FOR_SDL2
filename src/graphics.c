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

    int x1 = rect.x;
    int x2 = rect.x + rect.w;
    int y1 = rect.y;
    int y2 = rect.y + rect.h;

    if(x1<0 && x2<0) return;
    if(y1<0 && y2<0) return;
    if(x1>surface->w && x2>surface->w) return;
    if(y1>surface->h && y2>surface->h) return;

    if(x1<0) x1 = 0;
    if(y1<0) y1 = 0;
    if(x2>surface->w) x2 = surface->w;
    if(y2>surface->h) y2 = surface->h;

    for(int y=y1;y<y2;y++){
        for(int x=x1;x<x2;x++){
            buffer[y*surface_width+x] = color;
        }
    }
};