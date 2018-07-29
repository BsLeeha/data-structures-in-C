#pragma once
#include <stdio.h>

#define printf_format(x) _Generic((x), \
    char: "%c", \
    signed char: "%hhd", \
    unsigned char: "%hhu", \
    signed short: "%hd", \
    unsigned short: "%hu", \
    signed int: "%d", \
    unsigned int: "%u", \
    long int: "%ld", \
    unsigned long int: "%lu", \
    long long int: "%lld", \
    unsigned long long int: "%llu", \
    float: "%f", \
    double: "%f", \
    long double: "%Lf", \
    char *: "%s", \
    void *: "%p")

#define print(x)  printf(printf_format(x), x)

#define printnl(x) printf(printf_format(x), x), printf("\n")

#define printsp(x) printf(printf_format(x), x) printf(" ")

void int_print(const void *data);

void char_print(const void *data);