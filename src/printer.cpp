#include <stdarg.h>
#include <stdio.h>
#include "printer.hpp"

void print_line(size_t line, size_t column, const char * __restrict format, ...) {
    va_list args;
    va_start(args, format);

    printf("\x1b[%d;%dH", line, column);
    vprintf(format, args);

    va_end(args);
}