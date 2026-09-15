#include <stdbool.h>

#include "SDL2/SDL.h"
#include "wnd.h"

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
    manager->surface = main_surface;

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

        SDL_UpdateWindowSurface(main_window);
    }

    free(manager);
    SDL_DestroyWindow(main_window);
    SDL_Quit();
    return 0;
}