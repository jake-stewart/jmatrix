#include "../include/util.hpp"
#include "../include/color.hpp"

#include <stdio.h>
#include <string.h>

bool parse_int(char *number_string, int *number) {
    bool valid = true;
    int length = strlen(number_string);

    if (length == 0) {
        valid = false;
    }

    for (int i = 0; i < length; i++) {
        switch (number_string[i]) {
            case '0' ... '9': 
                break;

            default:
                valid = false;
                break;
        }
    }

    if (!valid) {
        printf("ERROR: Invalid number format: '%s'\n", number_string);
        return false;
    }

    sscanf(number_string, "%d", number);
    return true;
}

bool parse_color(char* hex_string, Color *color) {
    bool valid = true;
    int length = strlen(hex_string);

    if (hex_string[0] == '#') {
        hex_string += 1;
    }
    
    if (length != 6) {
        valid = false;
    }

    for (int i = 0; i < length; i++) {
        switch (hex_string[i]) {
            case '0' ... '9':
            case 'A' ... 'F':
            case 'a' ... 'f':
                break;

            default:
                valid = false;
                break;
        }
    }

    if (!valid) {
        printf("ERROR: Invalid hex color format: '%s'\n", hex_string);
        return false;
    }

    sscanf(hex_string,     "%02hhX", &color->r);
    sscanf(hex_string + 2, "%02hhX", &color->g);
    sscanf(hex_string + 4, "%02hhX", &color->b);

    return true;
}

void print_usage(char *title) {
    printf("Usage: %s {OPTIONS}\n\n", title);
    printf("OPTIONS:\n");
    printf("    --fg [hex color]\n");
    printf("        Set text color\n\n");
    printf("    --bg [hex color]\n");
    printf("        Set terminal background color for better fading\n\n");
    printf("    --ascii\n");
    printf("        Use ascii instead of anime\n\n");
    printf("    --gap [number]\n");
    printf("        Gap between falling text\n\n");
    printf("    --length [number]\n");
    printf("        Length of the falling text\n\n");
    printf("    --trail [number]\n");
    printf("        Size of the fading trail of the falling text\n\n");
    printf("    --speed [number]\n");
    printf("        Speed of the animation in FPS\n\n");
    printf("    --rarity [number]\n");
    printf("        The inverse chance of tails spawning (1/n)\n\n");
    printf("    --help | -h\n");
    printf("        Show this page\n");
}
