#include <SDL2/SDL.h>
#ifndef COLOR_H

#define COLOR_H

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

void init_color_palette(){
    
}
Uint32 parse_hex_color(char* hex);

void color_transition(int r_base, int g_base, int b_base, int r_to, int g_to, int b_to, int duration); 
void initialize_colors(SDL_Surface* surface);

#endif