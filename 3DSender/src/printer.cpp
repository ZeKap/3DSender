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

void print_keys(inputData input)
{
	print(4, 0, "                                ");
	print(4, 0, "buttons: %u", input.buttons);
	print(5, 0, "                                ");
	print(5, 0, "circle pad: x:%i, y:%i", input.circlePad.dx, input.circlePad.dy);
	print(6, 0, "                                ");
	print(6, 0, "accel: x:%i, y:%i, z:%i", input.accelerometer.x, input.accelerometer.y, input.accelerometer.z);
	print(7, 0, "                                ");
	print(7, 0, "gyro: x:%i, y:%i, z:%i", input.gyro.x, input.gyro.y, input.gyro.z);
}
