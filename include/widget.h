#ifndef WIDGET_H
#define WIDGET_H

#include <stddef.h>
#include <stdbool.h>
#include "utils.h"

#define TAB_HEIGHT 25

typedef struct WIDGET WIDGET;

typedef struct WIDGET_LIST {
    WIDGET* head;
    WIDGET* tail;
} WIDGET_LIST;

typedef struct SDL_Surface SDL_Surface;
typedef union SDL_Event SDL_Event;

bool WIDGET_LIST_APPEND(WIDGET_LIST* list,WIDGET* widget);
bool WIDGET_APPEND(WIDGET* parent,WIDGET* child);
void WIDGET_LIST_FREE_WIDGETS(WIDGET_LIST* list);
void WIDGET_LIST_DRAW_WIDGETS(WIDGET_LIST* list,SDL_Surface* surface);
WIDGET* WIDGET_LIST_HANDLE_EVENT(WIDGET_LIST* list,SDL_Event* e);

typedef enum {
    WND_TYPE,
} WIDGET_TYPE;

typedef struct WIDGET {
    WIDGET_TYPE type;

    int x,y;
    size_t w,h;
    uint8_t padding;

    WIDGET_LIST children;

    void (*destroy)(WIDGET* widget);
    void (*draw)(WIDGET* widget,SDL_Surface*);
    bool (*handle_event)(WIDGET*,SDL_Event*);

    bool hovered;
    bool dragging;

    WIDGET* parent;
    WIDGET* next;
    WIDGET* prev;
} WIDGET;

RECT ABSOLUTE_WIDGET_POS(WIDGET* widget);

bool INIT_WIDGET(
    WIDGET* widget,
    WIDGET_TYPE type,
    int x,int y,
    size_t w,size_t h,
    void (*destroy)(WIDGET*),
    void (*draw)(WIDGET*,SDL_Surface*),
    bool (*handle_event)(WIDGET*,SDL_Event*)
);

typedef struct WIDGET_MANAGER {
    WIDGET_LIST ROOT;
    SDL_Surface* surface;

    WIDGET* last_hovered;
    WIDGET* dragging;
} WIDGET_MANAGER;

WIDGET_MANAGER* CREATE_WIDGET_MANAGER(void);
void WIDGET_MANAGER_HANDLE_EVENT(WIDGET_MANAGER* manager,SDL_Event* e);
void DESTROY_WIDGET_MANAGER(WIDGET_MANAGER* manager);

extern WIDGET_LIST* TARGET_ROOT;
extern WIDGET* TARGET_WIDGET;

void SET_TARGET_ROOT(WIDGET_MANAGER* manager);

#endif