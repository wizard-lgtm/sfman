#include<SDL2/SDL.h>

#define WINDOW_W 400
#define WINDOW_H 600
#define PADDING 5
#define BG_R 0xFF
#define BG_G 0xFF
#define BG_B 0xFF

typedef enum {
    COLOR_PASTEL_BLUE,
    COLOR_GRAY,
    COLOR_WHITE,
    COLOR_TOTAL // track number

} ColorPaletteDark;

Uint32 colors_dark[COLOR_TOTAL];

void initialize_colors(SDL_Surface* surface) {
    // Her rengi SDL_MapRGB ile tanımlıyoruz
    colors_dark[COLOR_PASTEL_BLUE] = SDL_MapRGB(surface->format, 0xA7, 0xC7, 0xE7);
    colors_dark[COLOR_GRAY] = SDL_MapRGB(surface->format, 0x72, 0x72, 0xF7);
    colors_dark[COLOR_WHITE] = SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF);
}

/// Draws entry
///
void draw_list_entry(){

}

void draw_trackbar(SDL_Surface* surface){
    int w = 10;
    int h = WINDOW_H / 4; // always %20
    int x = WINDOW_W - PADDING - w;
    int y = PADDING;

    SDL_Rect trackbar = {x, y, w, h}; 

    SDL_FillRect(surface, &trackbar, colors_dark[COLOR_PASTEL_BLUE]);

}

/// 
/// Draws list for dir entries
///
void draw_list(SDL_Surface* surface){
    // declare widget 
    int border_size = 10;
    SDL_Rect list_widget;

    list_widget.h = WINDOW_H - PADDING * 2;
    list_widget.w = WINDOW_W - PADDING * 2;
    list_widget.x = PADDING;
    list_widget.y = PADDING;
    
    Uint32 color = SDL_MapRGB(surface->format, 0x72, 0x72, 0x72); // pastel gray

    SDL_FillRect(surface, &list_widget, color);

    // declare border
}

void draw_background(SDL_Surface* surface){
    SDL_Rect bg;
    bg.h = WINDOW_H;
    bg.w = WINDOW_W;
    bg.x = 0;
    bg.y = 0;
    Uint32 white = SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF);

    SDL_FillRect(surface, &bg, white);
}

void root(){


    // Init sdl
    SDL_Init(SDL_INIT_VIDEO);
    int running = 1;

    // Init window 
    SDL_Window* window =  SDL_CreateWindow("silly file manager", 0, 0, WINDOW_W, WINDOW_H, SDL_WINDOW_OPENGL);

    // Init Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    initialize_colors(surface);

    draw_background(surface);
    draw_list(surface);
    draw_trackbar(surface);

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