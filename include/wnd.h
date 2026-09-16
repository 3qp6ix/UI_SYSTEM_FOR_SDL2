#ifndef WND_H
#define WND_H

#include <stdint.h>
#include "widget.h"

typedef struct SDL_Surface SDL_Surface;

typedef struct WND {
    WIDGET widget;
    uint32_t backgroundColor;
} WND;

void DRAW_WND(WIDGET* widget,SDL_Surface* surface);
void DESTROY_WND(WIDGET* widget);

WND* CREATE_WND(
    int x,int y,
    size_t w,size_t h,
    uint32_t backgroundColor
);

#endif