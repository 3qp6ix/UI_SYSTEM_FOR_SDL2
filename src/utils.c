#include "utils.h"

#include <stdbool.h>

bool POINT_IN_RECT(int x,int y,RECT rect){
    if(x>=rect.x && x<rect.x+rect.w){
        if(y>=rect.y && y<rect.y+rect.h){
            return true;
        }
    }

    return false;
}