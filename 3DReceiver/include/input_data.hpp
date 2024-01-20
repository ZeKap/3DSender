#pragma once
#ifndef INPUT_DATA
#define INPUT_DATA
#include <cstdint>
#include <map>
#include <vector>
#include <iostream>

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

#define BIT(n) (1U << (n))
/// Key values
static std::map<std::string, u_int> s_keys{
	{"A", BIT(0)},			   ///< A
	{"B", BIT(1)},			   ///< B
	{"SELECT", BIT(2)},		   ///< Select
	{"START", BIT(3)},		   ///< Start
	{"DRIGHT", BIT(4)},		   ///< D-Pad Right
	{"DLEFT", BIT(5)},		   ///< D-Pad Left
	{"DUP", BIT(6)},		   ///< D-Pad Up
	{"DDOWN", BIT(7)},		   ///< D-Pad Down
	{"R", BIT(8)},			   ///< R
	{"L", BIT(9)},			   ///< L
	{"X", BIT(10)},			   ///< X
	{"Y", BIT(11)},			   ///< Y
	{"ZL", BIT(14)},		   ///< ZL (New 3DS only)
	{"ZR", BIT(15)},		   ///< ZR (New 3DS only)
	{"TOUCH", BIT(20)},		   ///< Touch (Not actually provided by HID)
	{"CSTICK_RIGHT", BIT(24)}, ///< C-Stick Right (New 3DS only)
	{"CSTICK_LEFT", BIT(25)},  ///< C-Stick Left (New 3DS only)
	{"CSTICK_UP", BIT(26)},	   ///< C-Stick Up (New 3DS only)
	{"CSTICK_DOWN", BIT(27)},  ///< C-Stick Down (New 3DS only)
	{"CPAD_RIGHT", BIT(28)},   ///< Circle Pad Right
	{"CPAD_LEFT", BIT(29)},	   ///< Circle Pad Left
	{"CPAD_UP", BIT(30)},	   ///< Circle Pad Up
	{"CPAD_DOWN", BIT(31)},	   ///< Circle Pad Down

	// Generic catch-all directions
	{"UP", BIT(6) | BIT(30)},	///< D-Pad Up or Circle Pad Up
	{"DOWN", BIT(7) | BIT(31)}, ///< D-Pad Down or Circle Pad Down
	{"LEFT", BIT(5) | BIT(29)}, ///< D-Pad Left or Circle Pad Left
	{"RIGHT", BIT(4) | BIT(28)} ///< D-Pad Right or Circle Pad Right
};

// Determines the key names from the button bitfield
std::vector<std::string> getKeys(std::uint32_t buttons);

#endif