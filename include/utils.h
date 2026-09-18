#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

typedef struct RECT {
    int x, y;
    size_t w,h;
} RECT;

bool POINT_IN_RECT(int x,int y,RECT rect);

#endif
