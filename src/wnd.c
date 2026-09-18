#include <stdlib.h>

#include "SDL2/SDL.h"
#include "wnd.h"
#include "widget.h"

#include "graphics.h"

#define TAB_COLOR 0xFF5566FF

bool WND_HANDLE_EVENT(WIDGET* widget,SDL_Event* e){
    if(!widget || !e)  return false;
    
    SDL_MouseMotionEvent m = e->motion;
    WIDGET* parent = widget->parent;
    WIDGET* w = widget;

    WND* wnd = (WND*)w;

    RECT abs = ABSOLUTE_WIDGET_POS(widget);

    bool in_rect = POINT_IN_RECT(m.x,m.y,(RECT){abs.x,abs.y,w->w,w->h+TAB_HEIGHT});
    bool in_tab = POINT_IN_RECT(m.x,m.y,(RECT){abs.x,abs.y,w->w,TAB_HEIGHT});

    // MOUSE MOTION
    if(e->type==SDL_MOUSEMOTION){
        if(widget->dragging){
            int new_x = m.x - (widget->parent? widget->parent->x : 0) - wnd->offset_x;
            int new_y = m.y - (widget->parent? widget->parent->y : 0) - wnd->offset_y;

            if(parent){
                uint8_t padding = w->padding;
                if(new_x<padding) new_x = padding;
                if(new_x+w->w>parent->w-padding) new_x = parent->w - w->w - padding;
                if(new_y<TAB_HEIGHT+padding) new_y = TAB_HEIGHT + padding;
                if(new_y+w->h>parent->h-padding) new_y = parent->h-padding-w->h;
            }

            widget->x = new_x;
            widget->y = new_y;

            return true;
        }

        if(in_rect){
            if(!widget->hovered) widget->hovered = true;
            return true;
        }
    }

    if(e->type==SDL_MOUSEBUTTONDOWN && e->button.button==SDL_BUTTON_LEFT){
        wnd->offset_x = m.x - (widget->parent? widget->parent->x : 0) - w->x;
        wnd->offset_y = m.y - (widget->parent? widget->parent->y : 0) - w->y;

        if(in_tab && wnd->canDrag){
            if(!widget->dragging) widget->dragging = true;
            if(widget->hovered) widget->hovered = false;
            return true;
        }
    }
    
    return false;
}

// DRAW WINDOW
void DRAW_WND(WIDGET* widget,SDL_Surface* surface){
    if(!widget || !widget) return;

    WIDGET* w = widget;
    WND* wnd = (WND*)widget;

    RECT abs = ABSOLUTE_WIDGET_POS(w);

    fill_rect(
        surface,
        (RECT){abs.x,abs.y,w->w,TAB_HEIGHT},
        wnd->tabColor
    );

    fill_rect(
        surface,
        (RECT){abs.x,abs.y+TAB_HEIGHT,w->w,w->h},
        w->hovered? 0xFFFF0000 : wnd->backgroundColor
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
        DRAW_WND,
        WND_HANDLE_EVENT
    );

    new_wnd->backgroundColor = backgroundColor;
    new_wnd->tabColor = TAB_COLOR;
    new_wnd->canDrag = false;

    if(TARGET_WIDGET){
        WIDGET_APPEND(TARGET_WIDGET,(WIDGET*)new_wnd);
    }else{
        WIDGET_LIST_APPEND(TARGET_ROOT,(WIDGET*)new_wnd);
    }

    return new_wnd;
};
