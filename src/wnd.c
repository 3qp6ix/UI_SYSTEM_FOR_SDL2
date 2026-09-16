#include <stdlib.h>

#include "SDL2/SDL.h"
#include "wnd.h"
#include "widget.h"

#include "graphics.h"


// DRAW WINDOW
void DRAW_WND(WIDGET* widget,SDL_Surface* surface){
    if(!widget || !widget) return;

    WIDGET* w = widget;
    WND* wnd = (WND*)widget;
    fill_rect(
        surface,
        (RECT){w->x,w->y,w->w,w->h},
        wnd->backgroundColor
    );
}

// FREE WINDOW
void DESTROY_WND(WIDGET* widget){
    if(!widget) return;
    WND* wnd = (WND*)widget;
    free(wnd);
};

WND* CREATE_WND(
    int x,int y,
    size_t w,size_t h,
    uint32_t backgroundColor
){
    if(!TARGET_ROOT && !TARGET_WIDGET) return NULL;
    WND* new_wnd = (WND*)malloc(sizeof(WND));

    if(!new_wnd) return NULL;
    INIT_WIDGET(
        &new_wnd->widget,
        WND_TYPE,
        x,y,w,h,
        DESTROY_WND,
        DRAW_WND
    );

    new_wnd->backgroundColor = backgroundColor;

    if(TARGET_WIDGET){
        WIDGET_LIST_APPEND(&TARGET_WIDGET->children,(WIDGET*)new_wnd);
    }else{
        WIDGET_LIST_APPEND(TARGET_ROOT,(WIDGET*)new_wnd);
    }

    return new_wnd;
};
