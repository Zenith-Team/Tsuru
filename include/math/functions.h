#pragma once

#include "math/constants.h"
#include "types.h"

// Power function for integers, with support for 64 bit integers
// @param x Base value
// @param y Exponent value
template <typename T>
inline T powi(T base, T exp) {
    T result = 1;
    while (exp) {
        if (exp & 1) result *= base;
        exp >>= 1;
        base *= base;
    }
    return result;
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
