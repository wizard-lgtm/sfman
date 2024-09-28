#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string.h>

Uint32 parse_hex_color(char* hex) {
    // Ensure the string starts with '#'
    if (hex[0] != '#') {
        fprintf(stderr, "Invalid hex color format. It should start with '#'.\n");
        return 0;
    }

    // Convert the hex string (ignoring the '#') to integer RGB values
    Uint32 red, green, blue;
    if (sscanf(hex + 1, "%02x%02x%02x", &red, &green, &blue) != 3) {
        fprintf(stderr, "Invalid hex color format.\n");
        return 0;
    }

    // Combine into Uint32 in the format 0xRRGGBB
    Uint32 color = (red << 16) | (green << 8) | blue;

    printf("%d\n", color);

    return color;
}

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
    // Initialize colors using parse_hex_color function
    colors_dark[COLOR_PASTEL_BLUE] = parse_hex_color("#a7c7e7");
    colors_dark[COLOR_GRAY] = parse_hex_color("#727272");  // Converted gray color to hex
    colors_dark[COLOR_WHITE] = parse_hex_color("#ffffff");
    colors_dark[COLOR_BLACK] = parse_hex_color("#000000");
    colors_dark[COLOR_RED] = parse_hex_color("#ff0000");
    colors_dark[COLOR_GREEN] = parse_hex_color("#00ff00");
    colors_dark[COLOR_YELLOW] = parse_hex_color("#ffff00");
    colors_dark[COLOR_ORANGE] = parse_hex_color("#ffa500");
    colors_dark[COLOR_PURPLE] = parse_hex_color("#800080");
}