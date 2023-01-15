#include <fstream>
#include "../include/option.hpp"
#include "../include/config_option_reader.hpp"

ConfigOptionReader::ConfigOptionReader(Config *config) {
    m_config = config;
}

#define BOOLEAN_ARG(ARG, NAME) \
    else if (option.key == ARG) { \
        if (option.hasValue) { \
            printf("Option '%s' did not expect a value\n", option.key.c_str()); \
            return false; \
        } \
        m_config->NAME = true; \
    }

#define STRING_ARG(ARG, NAME) \
    else if (option.key == ARG) { \
        if (!option.hasValue) { \
            printf("Option '%s' expected a value\n", option.key.c_str()); \
            return false; \
        } \
        m_config->NAME = option.value; \
    } \

#define INT_ARG(ARG, NAME) \
    else if (option.key == ARG) { \
        if (!option.hasValue) { \
            printf("Option '%s' expected a value\n", option.key.c_str()); \
            return false; \
        } \
        try{ \
            m_config->NAME = stoi(option.value);	\
        } \
        catch(std::exception &err) \
        { \
            printf("Option '%s' expected an int value\n", option.key.c_str()); \
            return false; \
        } \
    } \

#define COLOR_RGB_ARG(ARG, NAME) \
    else if (option.key == ARG) { \
        if (!option.hasValue) { \
            printf("Option '%s' expected a value\n", option.key.c_str()); \
            return false; \
        } \
        m_config->NAME = option.value; \
    } \

bool ConfigOptionReader::read(int argc, const char **argv) {
    std::vector<Option> options = parseOptions(argc, argv);
    for (int i = 0; i < options.size(); i++) {
        Option& option = options[i];

        if (option.key.empty()) {
            printf("Invalid argument: '%s'\n", option.value.c_str());
            return false;
        }
        BOOLEAN_ARG("ascii", ascii)
        BOOLEAN_ARG("help", ascii)
        INT_ARG("speed", speed)
        INT_ARG("trail", trail)
        INT_ARG("length", length)
        else {
            printf("Unknown option: '--%s'\n", option.key.c_str());
            return false;
        }
    }
    return true;
}

