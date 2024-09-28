#include<SDL2/SDL.h>
#include "fops.h"
#include "color.h"

#define WINDOW_W 400
#define WINDOW_H 600
#define PADDING 0
#define BG_R 0xFF
#define BG_G 0xFF
#define BG_B 0xFF

SDL_Surface* surface;
SDL_Window* window;
int running;
char** entries;
char* current_dir; 
Uint32 colors_dark[];

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
SDL_Rect draw_list_entry(int x, int y, Uint32 color){
    int w = WINDOW_W;
    int h = 25;
    SDL_Rect rect;
    rect.w = w;
    rect.h = h;
    rect.x = x;
    rect.y = y;

    SDL_FillRect(surface, &rect, color);

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

    list_widget.h = WINDOW_H;
    list_widget.w = WINDOW_W;
    list_widget.x = PADDING;
    list_widget.y = PADDING;
    
    

    SDL_FillRect(surface, &list_widget, parse_hex_color("#f7f7f7"));


    for (int i = 0; list[i] != NULL; i++) {
        int y;
        int x;
        if(i == 0) y = PADDING;
        else y = i * 25;
        x = PADDING;

        Uint32 color;
        color = parse_hex_color("#f7f7f7");
        draw_list_entry(x, y, color);
    }


    return list_widget;
}

SDL_Rect draw_background(){
    SDL_Rect bg;
    bg.h = WINDOW_H;
    bg.w = WINDOW_W;
    bg.x = 0;
    bg.y = 0;

    SDL_FillRect(surface, &bg, parse_hex_color("#fafafa"));
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