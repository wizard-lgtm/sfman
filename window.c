#include<SDL2/SDL.h>



void root(){

    int x = 0;
    int y = 0;
    int w = 600;
    int h = 300;

    // Init sdl
    SDL_Init(SDL_INIT_VIDEO);
    int running = 1;

    // Init window 
    SDL_Window* window =  SDL_CreateWindow("silly file manager", x, y, w, h, SDL_WINDOW_OPENGL);

    // Init Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));

    SDL_UpdateWindowSurface(window);

    SDL_Rect rect;
    rect.h = 200;
    rect.w = 300;
    rect.x = (x - rect.w) / 2;
    rect.y = (y - rect.y) / 2;

    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0xAA, 0xAB, 0xAC));
    SDL_UpdateWindowSurface(window);

    SDL_Event event;
    while(running){
        while(SDL_PollEvent(&event))
        if(event.type == SDL_QUIT){
            running = 0;
        }

    }
    // Exit 
    SDL_DestroyWindow(window);
    SDL_Quit();
}