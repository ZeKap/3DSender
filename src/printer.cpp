#include "printer.hpp"

size_t current_max_line = 1;

void print(const size_t line, const size_t column, const char *__restrict format, ...)
{
    va_list args;
    va_start(args, format);

    printf("\x1b[%d;%dH", line, column);
    vprintf(format, args);

    va_end(args);
    if (line >= current_max_line)
        current_max_line = line + 1;
}

void println(const size_t column, const char *__restrict format, ...)
{
    va_list args;
    va_start(args, format);

    printf("\x1b[%d;%dH", current_max_line, column);
    vprintf(format, args);

    va_end(args);
    current_max_line++;
}

void set_current_max_line(size_t line)
{
    current_max_line = line;
}

void clear_screen()
{
    consoleClear();
    set_current_max_line(0);
}

void print_connected_header(char *IP)
{
    print(1, 0, "Hello world!");

    print(2, 0, "Press START to exit.");
    print(3, 0, "IP: %s", IP);
}

void print_keys(u32 kheld)
{
    static u32 last_held = 0; // store last keys change
    if (kheld != last_held)
    {
        print(4, 0, "                    ");
        print(4, 0, "%u", kheld);
        last_held = kheld;
    }
}
