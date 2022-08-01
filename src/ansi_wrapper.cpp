#include "../include/ansi_wrapper.hpp"

#include <stdio.h>

#define ANSI_ESC "\x1b["

void set_color(uint8_t r, uint8_t g, uint8_t b) {
    printf(ANSI_ESC "38;2;%u;%u;%um", r, g, b);
}

void set_color(int code) {
    printf(ANSI_ESC "38;5;%dm", code);
}
