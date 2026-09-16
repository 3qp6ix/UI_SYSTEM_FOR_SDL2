#ifndef WIDGET_H
#define WIDGET_H

#include <stddef.h>
#include <stdbool.h>

typedef struct WIDGET WIDGET;

typedef struct WIDGET_LIST {
    WIDGET* head;
    WIDGET* tail;
} WIDGET_LIST;

typedef struct SDL_Surface SDL_Surface;

bool WIDGET_LIST_APPEND(WIDGET_LIST* list,WIDGET* widget);
void WIDGET_LIST_FREE_WIDGETS(WIDGET_LIST* list);
void WIDGET_LIST_DRAW_WIDGETS(WIDGET_LIST* list,SDL_Surface* surface);

typedef enum {
    WND_TYPE,
} WIDGET_TYPE;

typedef struct WIDGET {
    WIDGET_TYPE type;

    int x,y;
    size_t w,h;

    WIDGET_LIST children;

    void (*destroy)(WIDGET* widget);
    void (*draw)(WIDGET* widget,SDL_Surface*);

    WIDGET* parent;
    WIDGET* next;
    WIDGET* prev;
} WIDGET;

bool INIT_WIDGET(
    WIDGET* widget,
    WIDGET_TYPE type,
    int x,int y,
    size_t w,size_t h,
    void (*destroy)(WIDGET*),
    void (*draw)(WIDGET*,SDL_Surface*)
);

typedef struct WIDGET_MANAGER {
    WIDGET_LIST ROOT;
    SDL_Surface* surface;
} WIDGET_MANAGER;

WIDGET_MANAGER* CREATE_WIDGET_MANAGER(void);
void DESTROY_WIDGET_MANAGER(WIDGET_MANAGER* manager);

extern WIDGET_LIST* TARGET_ROOT;
extern WIDGET* TARGET_WIDGET;

void SET_TARGET_ROOT(WIDGET_MANAGER* manager);

#endif