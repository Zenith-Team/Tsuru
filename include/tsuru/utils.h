#pragma once

#include "types.h"
#include "prim/seadSafeString.h"
#include "math/seadBoundBox.h"

// Modified version of moveValueTo which supports overflowing/underflowing the value, used for smooth rotations.
inline bool moveValueWithOverflowTo(u32& value, u32 target, u32 step, bool subtract) {
    u32 counter = 0;
    u32 startValue = value;
    s64 offset = target - startValue;
    if (offset < 0) offset *= -1;

    if (counter + step < offset) {
        if (!subtract)
            value += step;
        else
            value -= step;

        counter += step;
        return false;
    }

    value = target;
    return true;
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

template <typename T>
static inline void swap(T& a, T& b) {
    const T temp = a;
    a = b;
    b = temp;
}

static inline const char* formatBool(bool value) {
    return value ? "true" : "false";
}

static inline bool intersects(const sead::BoundBox2f& a, const sead::BoundBox2f& b) {
    const sead::Vector2f& min_a = a.getMin();
    const sead::Vector2f& min_b = b.getMin();

    const sead::Vector2f& max_a = a.getMax();
    const sead::Vector2f& max_b = b.getMax();

    return min_a.x < max_b.x && max_a.x > min_b.x &&
           min_a.y < max_b.y && max_a.y > min_b.y;
}
