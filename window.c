#include<SDL2/SDL.h>

#define PADDING 10

/// 
/// Draws entry
///
void draw_list_entry(){

}
/// 
/// Draws list for dir entries
///
void draw_list(SDL_Surface* surface, int window_w, int window_h){
    // declare list 
    int border_size = 10;
    SDL_Rect list_widget;
    list_widget.h = window_h / 2 ;
    list_widget.w = window_h / 2;
    list_widget.x = border_size + PADDING;
    list_widget.y = border_size + PADDING;


    // declare border
    SDL_Rect border;
    list_widget.h = 200 - PADDING;
    list_widget.w = 200 - PADDING;
    list_widget.x = 0;
    list_widget.y = 0;
    

    // Declare colors 
    SDL_Color fg_color = {127,13,10};
    SDL_Color border_color = {255, 255, 255};

    Uint32 fg_mapped = SDL_MapRGB(surface->format, fg_color.r, fg_color.g, fg_color.b);
    Uint32 border_mapped = SDL_MapRGB(surface->format, border_color.r, border_color.g, border_color.b);



    // Draw border
    SDL_FillRect(surface, &border, border_mapped);

    // Draw widget
   


}

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

    draw_list(surface, w, h);

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