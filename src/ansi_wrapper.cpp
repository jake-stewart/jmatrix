#include "../include/ansi_wrapper.hpp"

#include <signal.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>

#define ANSI_ESC "\x1b["

void move(int x, int y) {
    printf(ANSI_ESC "%u;%uH", y + 1, x + 1);
}

void move_home() {
    printf(ANSI_ESC "H");
}

void set_color(uint8_t r, uint8_t g, uint8_t b) {
    printf(ANSI_ESC "38;2;%u;%u;%um", r, g, b);
}

void set_color(int code) {
    printf(ANSI_ESC "38;5;%dm", code);
}

void set_alternate_buffer(bool value) {
    printf(ANSI_ESC "?1049%c", value ? 'h' : 'l');
}

void clear_term() {
    printf(ANSI_ESC "2J");
}

void set_cursor(bool value) {
    printf(ANSI_ESC "?25%c", value ? 'h' : 'l');
}


void restore_term(void) {
    set_alternate_buffer(true);       // enter alternate buffer
    clear_term();                     // clean up the buffer
    set_cursor(true);                 // show the cursor
    set_alternate_buffer(false);      // return to the main buffer
    tcsetattr(1, TCSANOW, &initial);  // restore original termios params
}

void on_sig_term(int i) {
    exit(1);
    // since atexit has already registered a handler,
    // a call to exit(3) is all we actually need
}

void on_sig_resize(int i) {
    struct winsize ws;
    ioctl(1, TIOCGWINSZ, &ws);
    if (resize_callback != nullptr)
        resize_callback(ws.ws_col, ws.ws_row);
}


static char buf[50000]; /* buf must survive until stdout is closed */
void init_term(void) {
    // since we're using printf here, which doesn't play nicely
    // with non-canonical mode, we need to turn off buffering.
    // setvbuf(stdout, NULL, _IONBF, 0);

    setvbuf (stdout, buf, _IOFBF, sizeof(buf));

    struct termios t;
    tcgetattr(1, &t);
    initial = t;
    t.c_lflag &= (~ECHO & ~ICANON);
    tcsetattr(1, TCSANOW, &t);

    atexit(restore_term);
    signal(SIGWINCH, on_sig_resize);
    signal(SIGTERM, on_sig_term);
    signal(SIGINT, on_sig_term);

    set_alternate_buffer(true);
    clear_term();
    move_home();
    on_sig_resize(0);
}

void register_resize_callback(void (*func)(int, int)) {
    resize_callback = func;
}
