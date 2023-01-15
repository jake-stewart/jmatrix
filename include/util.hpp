#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <filesystem>

bool parse_int(char *number_string, int *number);
void print_usage(char *title);
std::string toLower(std::string s);
bool isVowel(char c);
std::filesystem::path expandUserPath(std::string user_path);

#endif
