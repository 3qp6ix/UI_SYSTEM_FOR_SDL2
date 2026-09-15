#include "widget.h"
#include <stdlib.h>

bool INIT_WIDGET(
    WIDGET* widget,
    WIDGET_TYPE type,
    int x,int y,
    size_t w,size_t h,
    void (*destroy)(WIDGET* widget)
){
    if(!widget) return false;
    *widget = (WIDGET){
        .type = type,
        .x = x,.y = y,
        .w= w,.h = h,
        .destroy = destroy,
        .children.head = NULL,
        .children.tail = NULL
    };

    return true;
}

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

WIDGET_MANAGER* CREATE_WIDGET_MANAGER(void){
    WIDGET_MANAGER* manager = (WIDGET_MANAGER*)malloc(sizeof(WIDGET_MANAGER));
    if(!manager) return NULL;
    *manager = (WIDGET_MANAGER){
        .ROOT.head = NULL,
        .ROOT.tail = NULL
    };

    return manager;
}

void DESTROY_WIDGET_MANAGER(WIDGET_MANAGER* manager){
    if(!manager) return;
    WIDGET_LIST_FREE_WIDGETS(&manager->ROOT);
    free(manager);
}

WIDGET_LIST* TARGET_ROOT = NULL;
WIDGET* TARGET_WIDGET = NULL;