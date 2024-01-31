#pragma once

#include "types.h"
#include "prim/seadSafeString.h"
#include "math/functions.h"
#include "math/seadBoundBox.h"

// Compare if two wide strings are equal
// @param str1 The first string to compare
// @param str2 The second string to compare
// @return < 0 if str1 is less than str2;
//           0 if str1 is identical to str2;
//         > 0 if str1 is greater than str2
extern "C" s32 wcscmp(const wchar_t* str1, const wchar_t* str2);

// Modified version of moveValueTo which supports overflowing/underflowing the value, used for smooth rotations
// @param value The variable to be modified
// @param target The value to move the variable towards
// @param step The amount that the variable will be moved by
// @param subtract Whether or not to subtract from the variable
// @return Whether or not the variable has reached the target
bool moveValueWithOverflowTo(u32& value, u32 target, u32 step, bool subtract);

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
