#include "../include/ansi_wrapper.hpp"
#include "../include/util.hpp"
#include "../include/data.hpp"
#include "../include/options.hpp"

#include <unistd.h>
#include <stdio.h>
#include <chrono>
#include <vector>

using std::vector;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

struct Tail
{
    int x;
    int y;
    int length;
    int seed;
};


vector<bool> entrances;
vector<Tail> tails;
int n_tails;

int        width, height;

const char (*style_chars)[4];
int        style_size;
int        style_width;

Color      fg                = {0, 255, 0};
Color      bg                = {0,   0, 0};

int        fade_trail_length = 8;
int        spacing;
int        max_tail_length   = 30;
int        min_tail_length   = 20;
int        rarity            = 20;


void new_tail(int x) {
    if (n_tails >= tails.size()) {
        tails.push_back(Tail());
    }
    tails[n_tails].x = x;
    tails[n_tails].y = -1;
    tails[n_tails].length = min_tail_length
        + (rand() % (max_tail_length - min_tail_length));
    tails[n_tails].seed = rand() % 12345;
    n_tails++;
    entrances[x] = false;
}

void remove_tail(int i) {
    tails[i] = tails[--n_tails];
}

void do_frame() {
    for (int i = 0; i < n_tails; i++) {
        Tail *tail = &tails[i];

        tail->y += 1;

        int tail_y = tail->y - tail->length;

        if (tail_y == 0) {
            entrances[tail->x] = true;
        }

        if (tail_y < height && tail_y >= 0) {
            move(tail->x, tail_y);
            putchar(' ');
        }
    }

    for (int fi = 1; fi < fade_trail_length; fi++) {
        float p1 = (float)(fi - 1) / fade_trail_length;
        float p2 = 1.0 - p1;

        set_color(
            p1 * fg.r + p2 * bg.r,
            p1 * fg.g + p2 * bg.g,
            p1 * fg.b + p2 * bg.b
        );

        for (int i = 0; i < n_tails; i++) {
            Tail *tail = &tails[i];
            int tail_y = tail->y - tail->length + fi;
            if (tail_y >= 0 && tail_y < height) {
                move(tail->x, tail_y);
                printf(
                    "%s", style_chars[(tail->seed * (tail_y + 1)) % style_size]
                );
            }
        }
    }

    set_color(fg.r, fg.g, fg.b);
    for (int i = 0; i < n_tails; i++) {
        Tail *tail = &tails[i];
        if (tail->y - 1 < height) {
            move(tail->x, tail->y - 1);
            printf(
                "%s", style_chars[(tail->seed * tail->y) % style_size]
            );
        }
    }

    set_color(255, 255, 255);
    for (int i = 0; i < n_tails; i++) {
        Tail *tail = &tails[i];
        if (tail->y < height) {
            move(tail->x, tail->y);
            printf(
                "%s", style_chars[(tail->seed * (tail->y + 1)) % style_size]
            );
        }
        else {
            if (tail->y - tail->length == height) {
                remove_tail(i--);
            }
        }
    }

    for (int i = 0; i < width - spacing; i += spacing) {
        if (!entrances[i]) {
            continue;
        }
        // 3 is my lucky number
        if (rand() % rarity == 0) {
            new_tail(i);
        }
    }
}

void on_resize(int w, int h) {
    width = w;
    height = h;
    n_tails = 0;
    for (int i = 0; i < entrances.size(); i++) {
        entrances[i] = true;
    }
    if (width > entrances.size()) {
        entrances.resize(width, true);
    }
    clear_term();
}


int main(int argc, char **argv) {
    Options options;

    if (!read_options(argc, argv, &options)) {
        return 1;
    }

    // if --help in options, then exit now
    if (options.view_help) {
        print_usage(argv[0]);
        return 0;
    }

    int frame_time;
    if (options.speed == 0) {
        frame_time = 2000;
    }
    frame_time = 1000 / options.speed;

    max_tail_length = options.length + 4;
    min_tail_length = max_tail_length / 2;

    rarity = options.rarity + 1;

    fade_trail_length = options.trail;
    if (fade_trail_length > min_tail_length) {
        fade_trail_length = min_tail_length;
    }

    fg = options.fg;
    bg = options.bg;

    spacing = options.gap + style_width + 2;

    if (options.ascii) {
        style_width = ASCII_WIDTH;
        style_size = ASCII_SIZE;
        style_chars = ASCII_CHARS;
    }
    else {
        style_width = ANIME_WIDTH;
        style_size = ANIME_SIZE;
        style_chars = ANIME_CHARS;
    }

    register_resize_callback(on_resize);
    init_term();
    set_cursor(false);

    while (true) {
        steady_clock::time_point start, end;

        start = steady_clock::now();
        do_frame();
        fflush(stdout);
        end = steady_clock::now();

        // fucking C++ disgusting piece of shit:
        int dur = duration_cast<milliseconds>(end - start).count();

        if (dur < frame_time)
            usleep((frame_time - dur) * 1000);
    }
}

