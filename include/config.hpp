#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <filesystem>
#include "ansi_style.hpp"
#include "style_manager.hpp"

struct Config
{
    int activeSourceStyle = NO_STYLE;

    int speed = 1;
    int gap = 1;
    int trail = 1;
    int length = 1;
    int rarity = 1;

    bool ascii = false;
    bool help = false;
};

#endif
