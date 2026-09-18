#include <stdlib.h>

#include "SDL2/SDL.h"
#include "widget.h"
#include "utils.h"

RECT ABSOLUTE_WIDGET_POS(WIDGET* widget){
    if(!widget) return (RECT){0,0,0,0};

    int x0 = widget->x;
    int y0 = widget->y;

    if(widget->parent){
        WIDGET* current_parent = widget->parent;
        while(current_parent){
            x0 += current_parent->x;
            y0 += current_parent->y;
            current_parent = current_parent->parent;
        }
    }

    return (RECT){x0,y0,0,0};
}

bool INIT_WIDGET(
    WIDGET* widget,
    WIDGET_TYPE type,
    int x,int y,
    size_t w,size_t h,
    void (*destroy)(WIDGET*),
    void (*draw)(WIDGET*,SDL_Surface*),
    bool (*handle_event)(WIDGET*,SDL_Event*)
){
    if(!widget) return false;
    *widget = (WIDGET){
        .type = type,
        .x = x,.y = y,
        .w = w,.h = h,
        .padding = 2,
        .destroy = destroy,
        .draw = draw,
        .handle_event = handle_event,
        .hovered = false,
        .dragging = false,
        .parent = NULL,
        .next = NULL,
        .prev = NULL,
        .children.head = NULL,
        .children.tail = NULL
    };

    return true;
}

// APPEND A WIDGET TO THE LINKED LIST
bool WIDGET_LIST_APPEND(WIDGET_LIST* list,WIDGET* widget){
    if(!list || !widget) return false;

    widget->next = NULL;
    if(!list->head){
        list->head = widget;
        widget->prev = NULL;
    }else{
        list->tail->next = widget;
        widget->prev = list->tail;
    }

    list->tail = widget;
    return true;
}

// APPEND A WIDGET TO A WIDGET
bool WIDGET_APPEND(WIDGET* parent,WIDGET* child){
    if(!parent || !child) return false;
    bool added = WIDGET_LIST_APPEND(&parent->children,child);
    if(parent->type==WND_TYPE) child->y+=TAB_HEIGHT;

    child->x+=parent->padding;
    child->y+=parent->padding;

    if(added) child->parent = parent;
    return added;
}

// WIDGET->destroy() (free every widget in the linked list)
void WIDGET_LIST_FREE_WIDGETS(WIDGET_LIST* list){
    if(!list || !list->head) return;

    WIDGET* current = list->head;
    while(current){
        WIDGET* next = current->next;
        WIDGET_LIST_FREE_WIDGETS(&current->children);
        if(current->destroy) current->destroy(current);
        current = next;
    }
}

// WIDGET->draw(...) (draw every widget in the linked list)
void WIDGET_LIST_DRAW_WIDGETS(WIDGET_LIST* list,SDL_Surface* surface){
    if(!list || !surface) return;
    WIDGET* current = list->head;
    while(current){
        if(current->draw) current->draw(current,surface);
        WIDGET_LIST_DRAW_WIDGETS(&current->children,surface);
        current = current->next;
    }
}

WIDGET* WIDGET_LIST_HANDLE_EVENT(WIDGET_LIST* list, SDL_Event* e){
    if (!list || !e) return NULL;

    WIDGET* current = list->head;
    while (current) {
        WIDGET* widget =  WIDGET_LIST_HANDLE_EVENT(&current->children, e);

        if (widget) return widget;

        if (current->handle_event && current->handle_event(current, e)){
            return current;
        }

        current = current->next;
    }

    return NULL;
}

WIDGET_MANAGER* CREATE_WIDGET_MANAGER(void){
    WIDGET_MANAGER* manager = (WIDGET_MANAGER*)malloc(sizeof(WIDGET_MANAGER));
    if(!manager) return NULL;
    *manager = (WIDGET_MANAGER){
        .ROOT.head = NULL,
        .ROOT.tail = NULL
    };

    return manager;
}

void WIDGET_MANAGER_HANDLE_EVENT(WIDGET_MANAGER* manager,SDL_Event* e){
    if(!manager || !e) return;
    WIDGET* handled = WIDGET_LIST_HANDLE_EVENT(&manager->ROOT,e);

    if(e->type==SDL_MOUSEMOTION){
        if(handled!=manager->last_hovered){
            if(manager->last_hovered) manager->last_hovered->hovered = false;
            manager->last_hovered = handled;
        }
    }

    if(e->type==SDL_MOUSEBUTTONDOWN && e->button.button==SDL_BUTTON_LEFT){
        if(handled && handled->dragging){
            manager->dragging = handled;
        }
    }

    if(e->type==SDL_MOUSEBUTTONUP && e->button.button==SDL_BUTTON_LEFT){
        if(manager->dragging){
            manager->dragging->dragging = false;
            manager->dragging = NULL;
        }
    }
}

void DESTROY_WIDGET_MANAGER(WIDGET_MANAGER* manager){
    if(!manager) return;
    WIDGET_LIST_FREE_WIDGETS(&manager->ROOT);
    free(manager);
}

WIDGET_LIST* TARGET_ROOT = NULL;
WIDGET* TARGET_WIDGET = NULL;

void SET_TARGET_ROOT(WIDGET_MANAGER* manager){
    if(!manager) return;
    TARGET_ROOT = &manager->ROOT;
}