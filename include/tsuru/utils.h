#pragma once

#include <types.h>

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
