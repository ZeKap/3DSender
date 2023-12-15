#include <cstdint>
#ifndef INPUT_DATA
#define INPUT_DATA

struct circlePosition
{
	std::int16_t dx;
	std::int16_t dy;
};

struct accelVector
{
	std::int16_t x;
	std::int16_t y;
	std::int16_t z;
};

struct angularRate
{
	std::int16_t x;
	std::int16_t y;
	std::int16_t z;
};

struct inputData
{
	std::uint32_t buttons;
	circlePosition circlePad;
	accelVector accelerometer;
	angularRate gyro;
};

#endif