#ifndef UTIL_HPP
#define UTIL_HPP

#include "../include/color.hpp"

bool parse_color(char* hex_string, Color *color);
bool parse_int(char *number_string, int *number);
void print_usage(char *title);

#endif
