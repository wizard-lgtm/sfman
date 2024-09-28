#include<SDL2/SDL.h>
#include "fops.h"

#define WINDOW_W 400
#define WINDOW_H 600
#define PADDING 5
#define BG_R 0xFF
#define BG_G 0xFF
#define BG_B 0xFF

SDL_Surface* surface;
SDL_Window* window;
int running;
char** entries;
char* current_dir; 

typedef enum {
    COLOR_PASTEL_BLUE,
    COLOR_GRAY,
    COLOR_WHITE,
    COLOR_BLACK,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_ORANGE,
    COLOR_PURPLE,
    COLOR_TOTAL // track number of colors
} ColorPaletteDark;

Uint32 colors_dark[COLOR_TOTAL];

void initialize_colors(SDL_Surface* surface) {
    // Initialize colors using SDL_MapRGB
    colors_dark[COLOR_PASTEL_BLUE] = SDL_MapRGB(surface->format, 0xA7, 0xC7, 0xE7);
    colors_dark[COLOR_GRAY] = SDL_MapRGB(surface->format, 0x72, 0x72, 0x72);   // Fixed the gray color value
    colors_dark[COLOR_WHITE] = SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF);
    colors_dark[COLOR_BLACK] = SDL_MapRGB(surface->format, 0x00, 0x00, 0x00);
    colors_dark[COLOR_RED] = SDL_MapRGB(surface->format, 0xFF, 0x00, 0x00);
    colors_dark[COLOR_GREEN] = SDL_MapRGB(surface->format, 0x00, 0xFF, 0x00);
    colors_dark[COLOR_YELLOW] = SDL_MapRGB(surface->format, 0xFF, 0xFF, 0x00);
    colors_dark[COLOR_ORANGE] = SDL_MapRGB(surface->format, 0xFF, 0xA5, 0x00);
    colors_dark[COLOR_PURPLE] = SDL_MapRGB(surface->format, 0x80, 0x00, 0x80);
}

void update_window(){
    SDL_UpdateWindowSurface(window);
}

typedef void (*HoverHandler)(SDL_Rect*);
void handle_hover_rect(SDL_Rect* rect, HoverHandler handler){
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);


    if(mouse_x > rect->x && mouse_x < rect->x + rect->w
    && mouse_y > rect->y && mouse_y < rect->y + rect->h
    ){
        handler(rect);
    }
}

SDL_Rect draw_trackbar(){
    int w = 10;
    int h = WINDOW_H / 4; // always %20
    int x = WINDOW_W - PADDING - w;
    int y = PADDING;

    SDL_Rect trackbar = {x, y, w, h}; 

    SDL_FillRect(surface, &trackbar, colors_dark[COLOR_PASTEL_BLUE]);

    return trackbar;
}


void trackbar_hover(SDL_Rect* rect){
    SDL_FillRect(surface, rect, colors_dark[COLOR_GRAY]);
}

void list_entry_hover(SDL_Rect* rect){
    SDL_FillRect(surface, rect, colors_dark[COLOR_PURPLE]);
}
///
/// Draws entry
///
SDL_Rect draw_list_entry(int x, int y){
    int w = WINDOW_W - 50;
    int h = 50;
    SDL_Rect rect;
    rect.w = w;
    rect.h = h;
    rect.x = x;
    rect.y = y;

    SDL_FillRect(surface, &rect, colors_dark[COLOR_WHITE]);

    handle_hover_rect(&rect, list_entry_hover);


    return rect;
}
/// 
/// Draws list for dir entries
///
SDL_Rect draw_list(char** list){
    // declare widget 
    int border_size = 10;
    SDL_Rect list_widget;

    list_widget.h = WINDOW_H - PADDING * 2;
    list_widget.w = WINDOW_W - PADDING * 2;
    list_widget.x = PADDING;
    list_widget.y = PADDING;
    
    

    SDL_FillRect(surface, &list_widget, colors_dark[COLOR_ORANGE]);


    for (int i = 0; list[i] != NULL; i++) {
        int y;
        int x;
        if(i == 0) y = PADDING + 5;
        else y = i * 75 + 5;
        x = PADDING + 20;

        printf("Entry %d: %s\n", i + 1, list[i]);
        draw_list_entry(x, y);
    }


    return list_widget;
}

SDL_Rect draw_background(){
    SDL_Rect bg;
    bg.h = WINDOW_H;
    bg.w = WINDOW_W;
    bg.x = 0;
    bg.y = 0;

    SDL_FillRect(surface, &bg, colors_dark[COLOR_WHITE]);
}

char* change_dir(char* current_dir, char* new_dir){
    char* new_ptr = realloc(current_dir, strlen(new_dir)+ 1);
    return new_ptr;
}
void init_sdl(){
    // Init sdl
    SDL_Init(SDL_INIT_VIDEO);
    running = 1;

    // Init window 
    window =  SDL_CreateWindow("silly file manager", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, SDL_WINDOW_OPENGL);
    
    surface = SDL_GetWindowSurface(window);

}
void init_variables(){
    // Init variables

    initialize_colors(surface);

    current_dir = malloc(strlen(".") + 1 );
    strcpy(current_dir, ".");
    entries = list_dir_entries(current_dir);
}
void close_window(){
    // Exit 
    SDL_DestroyWindow(window);
    free(current_dir);
    // Free list
    for (int i = 0; entries[i] != NULL; i++) {
        free(entries[i]); // Correctly free each entry
    }
    free(entries); // Finally, free the list itself
    SDL_Quit();
} 

void mainloop(){
    SDL_Event event;


    SDL_Rect background = draw_background();
    

    while(running){
    SDL_Rect list_widget = draw_list(entries);
    SDL_Rect trackbar = draw_trackbar();
    handle_hover_rect(&trackbar, trackbar_hover); 
        while(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT){
                running = 0;
            }
        SDL_UpdateWindowSurface(window);
    }
}
void root(){
    init_sdl();
    init_variables();
    mainloop();
    close_window();
}