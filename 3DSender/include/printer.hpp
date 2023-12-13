#pragma once
#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <3ds.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdio.h>
#include "input_data.hpp"

/**
 * @brief Displays a line of text at the specified line and column.
 */
void print(const size_t line, const size_t column, const char *__restrict str, ...);

/**
 * @brief Displays a line of text at the specified column, after the others.
 */
void println(const size_t column, const char *__restrict str, ...);

/**
 * @brief Reset current_max_line, to restart writting where we want, when we refresh the screen for example_
 */
void set_current_max_line(size_t line);

/**
 * @brief clear everything that was displayed on screen and reset line counter
 */
void clear_screen();

/**
 * @brief print Hello World and the smallest interface ever on a 3DS
 */
void print_connected_header(char *IP);

/**
 * @brief displays keys given in parameters
 */
void print_keys(inputData input);

#endif
