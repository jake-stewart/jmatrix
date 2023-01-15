#include "../include/options.hpp"
#include "../include/util.hpp"

#include <string.h>
#include <stdio.h>

bool read_options(int argc, char **argv, Options *options) {
    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];

        if (strcmp(arg, "--speed") == 0) {
            if (++i == argc) {
                printf("ERROR: --speed is missing a value\n");
                return false;
            }
            if (!parse_int(argv[i], &options->speed)) {
                return false;
                }
        }

        else if (strcmp(arg, "--ascii") == 0) {
            options->ascii = true;
        }

        else if (strcmp(arg, "--gap") == 0) {
            if (++i == argc) {
                printf("ERROR: --gap is missing a value\n");
                return false;
            }
            if (!parse_int(argv[i], &options->gap)) {
                return false;
            }
        }

        else if (strcmp(arg, "--trail") == 0) {
            if (++i == argc) {
                printf("ERROR: --trail is missing a value\n");
                return false;
            }
            if (!parse_int(argv[i], &options->trail)) {
                return false;
            }
        }

        else if (strcmp(arg, "--length") == 0) {
            if (++i == argc) {
                printf("ERROR: --length is missing a value\n");
                return false;
            }
            if (!parse_int(argv[i], &options->length)) {
                return false;
            }
        }

        else if (strcmp(arg, "--rarity") == 0) {
            if (++i == argc) {
                printf("ERROR: --rarity is missing a value\n");
                return false;
            }
            if (!parse_int(argv[i], &options->rarity)) {
                return false;
            }
        }

        else if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) {
            options->view_help = true;
            break;
        }

        else {
            printf("Unknown option: '%s'\n", arg);
            printf("See 'jmatrix --help' for usage information\n");
            return false;
        }
    }

    return true;
}
