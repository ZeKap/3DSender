#ifndef INPUT_DATA
#define INPUT_DATA

#include <3ds.h>

/**
 * @brief all the data we want to send from the inputs of the console to the client
 */
struct inputData
{
	u32 buttons;
	circlePosition circlePad;
	accelVector accelerometer;
	angularRate gyro;
};

bool operator==(const inputData &left, const inputData &right);

bool operator==(const circlePosition &left, const circlePosition &right);

bool operator==(const accelVector &left, const accelVector &right);

bool operator==(const angularRate &left, const angularRate &right);
#endif // INPUT_DATA