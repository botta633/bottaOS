#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>
#include <stdint.h>




void initialize_terminal();
void print_char(char c, int color);
size_t strlen(const char* str);
void print_message(const char* msg);
#endif
