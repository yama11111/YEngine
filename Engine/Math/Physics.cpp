#include "Physics.h"
#include <cmath>

float YMath::CalcSpeed(const float acceleration, const float time, const float initiale)
{
    // v = at + v0
    return (acceleration * time) + initiale;
}

float YMath::CalcSpeedUsingDistance(const float acceleration, const float distance, const float initiale)
{
    // v^2 = v0^2 + 2ax
    return std::sqrtf((initiale * initiale) + (2.0f * acceleration * distance));
}

float YMath::CalcAcceleration(const float speed, const float time, const float initiale)
{
    // a = (v - v0) / t
    return (speed - initiale) / time;
}

float YMath::CalcDistance(const float acceleration, const float time, const float initiale)
{
    // x = v0t + 1/2 * a(t^2)
    return (initiale * time) + (0.5f * acceleration * time * time);
}

float YMath::CalcDistanceUsingSpeed(const float speed, const float time, const float initiale)
{
    // x = 1/2 * (v0 + v)t
    return 0.5f * (initiale + speed) * time;
}

float YMath::CalcGravityAcceleration(const float time)
{
    // 9.8m/s^2
    return 9.8f * time;
}

float YMath::CalcGravitySpeed(const float time, const float initiale)
{
    return CalcSpeed(CalcGravityAcceleration(time), time, initiale);
}

float YMath::CalcDistanceUsingGravity(const float time, const float initiale)
{
    return CalcDistance(CalcGravityAcceleration(time), time, initiale);
}

float YMath::CalcResistingForce(const float proportion, const float speed)
{
    // F = kv
    return proportion * speed;
}
