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

    WND* windowA = CREATE_WND(50,50,400,300,0xFF252A34);
    windowA->tabColor = 0xFF3B82F6;

    TARGET_WIDGET = (WIDGET*)windowA;
    WND* inner_window = CREATE_WND(50,50,200,100,0xFF343B49);
    inner_window->tabColor = 0xFF60A5BA;

    bool running = true;
    SDL_Event e;
    while(running){
        while(SDL_PollEvent(&e)){
            WIDGET_MANAGER_HANDLE_EVENT(manager,&e);
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