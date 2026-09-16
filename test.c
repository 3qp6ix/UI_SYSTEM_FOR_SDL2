#include <stdbool.h>

#include "SDL2/SDL.h"
#include "wnd.h"
#include "graphics.h"

int WIDTH = 900;
int HEIGHT = 600;

int main(int argc,char** argv){
    if(SDL_Init(SDL_INIT_VIDEO)!=0) return 1;

    SDL_Window* main_window = SDL_CreateWindow(
        "Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,HEIGHT,
        0
    );

    if(!main_window);

    SDL_Surface* main_surface = SDL_GetWindowSurface(main_window);

    WIDGET_MANAGER* manager = CREATE_WIDGET_MANAGER();
    SET_TARGET_ROOT(manager);
    manager->surface = main_surface;

    WND* windowA = CREATE_WND(20,20,400,300,0xFF444444);

    bool running = true;
    SDL_Event e;
    while(running){
        while(SDL_PollEvent(&e)){
            switch(e.type){
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }

        fill_rect(main_surface,(RECT){0,0,WIDTH,HEIGHT},0xFFFFFFFF);

        WIDGET_LIST_DRAW_WIDGETS(TARGET_ROOT,main_surface);
        SDL_UpdateWindowSurface(main_window);
    }

    DESTROY_WIDGET_MANAGER(manager);
    SDL_DestroyWindow(main_window);
    SDL_Quit();
    return 0;
}