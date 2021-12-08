#pragma once

#include "math/constants.h"
#include "types.h"

// @return Sine value of the given param
f32 sinf(f32 x);
// @return Cosine value of the given param
f32 cosf(f32 x);
// @return Tangent value of the given param
f32 tanf(f32 x);
// @return Arcsine value of the given param
f32 asinf(f32 x);
// @return Arccosine value of the given param
f32 acosf(f32 x);
// @return Arctangent2 value of the given params
f32 atan2f(f32 x, f32 y);
// @return Exponent value of the given param raised to e
f32 expf(f32 x);
// @return Logarithm value of the given param
f32 logf(f32 x);
// @param x Number to be exponentiated
// @param y Value to raise the power to
// @return Value of the given param raised to the power param
f32 powf(f32 x, f32 y);
// @return Square root of the given param
f32 sqrtf(f32 x);
f32 fmodf(f32 x, f32 y);

// @return Square of the given param
inline f32 pow2f(f32 x) { return x * x; }

// @return The given param without a sign
inline f32 fabsf(f32 x) { return (x < 0.0f) ? -x : x; }

inline f32 degToRad(f32 deg) { return (deg * M_PI) / 180.0f; }

inline f32 radToDeg(f32 rad) { return (rad * 180.0f) / M_PI; }

inline u32 fixRad(f32 val) {
    val = fmodf(val, M_2PI);
    if (val < 0.0f) val += M_2PI;
    return val * 683565276;
}

inline f32 unfixRad(u32 val) {
    return val / 683565248.0f;
}

// Converts degrees to integer rotations
// @param val Degrees to convert
// @return Converted integer rotation
inline u32 fixDeg(f32 val) {
    val = fmodf(val, 360.0f);
    if (val < 0.0f) val += 360.0f;
    return val * 11930465.0f;
}

// Converts integer rotation to degrees
// @param val Integer rotation to convert
// @return Converted degrees
inline f32 unfixDeg(u32 val) {
    return (val / 11930465.0f);
}

inline Vec2f radToDirection(f32 rad) {
    return Vec2f(sinf(rad), cosf(rad));
}

inline Vec2f degToDirection(f32 deg) {
    return radToDirection(degToRad(deg));
}

// @param x First value to compare
// @param y Second value to compare
// @return The smallest value given
template <class T>
inline const T& min(const T& x, const T& y) {
    return !(y < x) ? x : y;
}

// @param x First value to compare
// @param y Second value to compare
// @return The largest value given
template <class T>
inline const T& max(const T& x, const T& y) {
    return (x < y) ? y : x;
}

// Gets the percentage represented by a number within a given range
// @param value The number
// @param min The start value of the range
// @param max The end value of the range
// @return The percentage
inline f32 percentFromValue(f32 value, f32 min, f32 max) { return (((value - min) * 100) / (max - min)) / 100; }

// Gets the number represented by a percentage of a given range
// @param percent The percentage
// @param min The start value of the range
// @param max The end value of the range
// @return The number
inline f32 valueFromPercent(f32 percent, f32 min, f32 max) { return (percent * 100 * (max - min) / 100) + min; }
