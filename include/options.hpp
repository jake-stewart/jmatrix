#ifndef OPTIONS_H
#define OPTIONS_H

#include "color.hpp"

struct Options {
    int   gap         = 1;
    int   rarity      = 20;
    int   speed       = 30;
    int   length      = 30;
    int   trail       = 30;
    bool  ascii       = false;
    bool  view_help   = false;
    Color fg          = {0, 255, 0};
    Color bg          = {0, 0, 0};
};

bool read_options(int argc, char **argv, Options *options);

#endif
