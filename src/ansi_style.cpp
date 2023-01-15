#include "../include/ansi_style.hpp"
#include <sstream>

bool convert16RGB(Color16 from, ColorRGB *to) {
    switch (from) {
        case BLACK:
            *to = {0, 0, 0};
            break;
        case RED:
            *to = {255, 0, 0};
            break;
        case GREEN:
            *to = {0, 255, 0};
            break;
        case YELLOW:
            *to = {255, 255, 0};
            break;
        case BLUE:
            *to = {0, 0, 255};
            break;
        case MAGENTA:
            *to = {255, 0, 255};
            break;
        case CYAN:
            *to = {0, 255, 255};
            break;
        case WHITE:
            *to = {200, 200, 200};
            break;
        case BRIGHT_BLACK:
            *to = {64, 64, 64};
            break;
        case BRIGHT_RED:
            *to = {255, 64, 64};
            break;
        case BRIGHT_GREEN:
            *to = {64, 255, 64};
            break;
        case BRIGHT_YELLOW:
            *to = {255, 255, 64};
            break;
        case BRIGHT_BLUE:
            *to = {64, 64, 255};
            break;
        case BRIGHT_MAGENTA:
            *to = {255, 64, 255};
            break;
        case BRIGHT_CYAN:
            *to = {64, 255, 255};
            break;
        case BRIGHT_WHITE:
            *to = {255, 255, 255};
            break;
        default:
            return false;
    }
    return true;
}

ColorRGB* AnsiStyle::getRGB() {
    if (m_fg_type == COLOR_RGB) {
        return &m_fg_rgb;
    }
    else if (m_fg_type == COLOR_16) {
        if (convert16RGB(m_fg_16, &m_fg_rgb)) {
            return &m_fg_rgb;
        }
    }
    return nullptr;
}

AnsiStyle& AnsiStyle::fg(Color16 color) {
    if (color >= BRIGHT_BLACK) {
        return fg((int)color);
    }
    m_fg_type = COLOR_16;
    m_fg_16 = color;
    return *this;
}

AnsiStyle& AnsiStyle::bg(Color16 color) {
    if (color >= BRIGHT_BLACK) {
        return bg((int)color);
    }
    m_bg_type = COLOR_16;
    m_bg_16 = color;
    return *this;
}

AnsiStyle& AnsiStyle::fg(int color) {
    m_fg_type = COLOR_256;
    m_fg_256 = color;
    return *this;
}

AnsiStyle& AnsiStyle::bg(int color) {
    m_bg_type = COLOR_256;
    m_bg_256 = color;
    return *this;
}

AnsiStyle AnsiStyle::fg(ColorRGB color) {
    m_fg_type = COLOR_RGB;
    m_fg_rgb = color;
    return *this;
}

AnsiStyle AnsiStyle::bg(ColorRGB color) {
    m_bg_type = COLOR_RGB;
    m_bg_rgb = color;
    return *this;
}

AnsiStyle& AnsiStyle::bold() {
    m_bold = true;
    return *this;
}

AnsiStyle& AnsiStyle::italic() {
    m_italic = true;
    return *this;
}

AnsiStyle& AnsiStyle::underline() {
    m_underline = LINE;
    return *this;
}

AnsiStyle& AnsiStyle::blink() {
    m_blink = true;
    return *this;
}

AnsiStyle& AnsiStyle::standout() {
    m_standout = true;
    return *this;
}

AnsiStyle& AnsiStyle::strikethrough() {
    m_strikethrough = true;
    return *this;
}

AnsiStyle& AnsiStyle::dim() {
    m_dim = true;
    return *this;
}

AnsiStyle& AnsiStyle::underline(UnderlineType type) {
    m_underline = type;
    return *this;
}

std::string AnsiStyle::build() {
    std::stringstream ss;
    ss << "\x1b[0";

    switch (m_fg_type) {
        case COLOR_16:
            ss << ";" << (30 + m_fg_16);
            break;
        case COLOR_256:
            ss << ";38;5;" << m_fg_256;
            break;
        case COLOR_RGB:
            ss << ";38;2;"
                << (int)m_fg_rgb.r << ";"
                << (int)m_fg_rgb.g << ";"
                << (int)m_fg_rgb.b;
            break;
        case NO_COLOR:
            break;
    }

    switch (m_bg_type) {
        case COLOR_16:
            ss << ";" << (40 + m_bg_16);
            break;
        case COLOR_256:
            ss << ";48;5;" << m_bg_256;
            break;
        case COLOR_RGB:
            ss << ";48;2;"
                << (int)m_bg_rgb.r << ";"
                << (int)m_bg_rgb.g << ";"
                << (int)m_bg_rgb.b;
            break;
        case NO_COLOR:
            break;
    }

    if (m_bold)          ss << ";1";
    if (m_dim)           ss << ";2";
    if (m_italic)        ss << ";3";
    if (m_blink)         ss << ";5";
    if (m_standout)      ss << ";7";
    if (m_strikethrough) ss << ";9";

    if (m_underline) {
        ss << ";4";
        switch (m_underline) {
            case DOUBLE:
                ss << ":2";
                break;
            case CURLY:
                ss << ":3";
                break;
            case DOTTED:
                ss << ":4";
                break;
            case DASHED:
                ss << ":5";
                break;
            default:
                break;
        }
    }

    ss << "m";
    return ss.str();
}
