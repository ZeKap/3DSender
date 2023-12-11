#include "input_data.hpp"

bool operator==(const inputData &left, const inputData &right)
{
    return (left.buttons == right.buttons && left.circlePad == right.circlePad && left.accelerometer == right.accelerometer && left.gyro == right.gyro);
}

bool operator==(const circlePosition &left, const circlePosition &right)
{
    return left.dx == right.dx && left.dy == right.dy;
}

bool operator==(const accelVector &left, const accelVector &right)
{
    return left.x == right.x && left.y == right.y && left.z == right.z;
}

bool operator==(const angularRate &left, const angularRate &right)
{
    return left.x == right.x && left.y == right.y && left.z == right.z;
}
