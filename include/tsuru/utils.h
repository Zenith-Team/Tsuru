#pragma once

#include "types.h"

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

// Returns the nth bit of a 64 bit integer from the right
// @param val The integer to be evaluated
// @param nth The bit index from the right (1 indexed)
// @return The value of the retrieved bit
forceinline bool nthBit64Right(u64 val, u64 nth) { return (val >> (nth - 1)) & 1; }
// Returns the nth bit of a 32 bit integer from the right
// @param val The integer to be evaluated
// @param nth The bit index from the right (1 indexed)
// @return The value of the retrieved bit
forceinline bool nthBit32Right(u32 val, u32 nth) { return (val >> (nth - 1)) & 1; }
// Returns the nth bit of a 16 bit integer from the right
// @param val The integer to be evaluated
// @param nth The bit index from the right (1 indexed)
// @return The value of the retrieved bit
forceinline bool nthBit16Right(u16 val, u16 nth) { return (val >> (nth - 1)) & 1; }
// Returns the nth bit of a 8 bit integer from the right
// @param val The integer to be evaluated
// @param nth The bit index from the right (1 indexed)
// @return The value of the retrieved bit
forceinline bool nthBit8Right(u8 val, u8 nth) { return (val >> (nth - 1)) & 1; }

// Returns the nth bit of a 64 bit integer from the left
// @param val The integer to be evaluated
// @param nth The bit index from the right (1 indexed)
// @return The value of the retrieved bit
forceinline bool nthBit64Left(u64 val, u64 nth) { return (val << (nth - 1)) & 1; }
// Returns the nth bit of a 32 bit integer from the left
// @param val The integer to be evaluated
// @param nth The bit index from the right (1 indexed)
// @return The value of the retrieved bit
forceinline bool nthBit32Left(u32 val, u32 nth) { return (val << (nth - 1)) & 1; }
// Returns the nth bit of a 16 bit integer from the left
// @param val The integer to be evaluated
// @param nth The bit index from the right (1 indexed)
// @return The value of the retrieved bit
forceinline bool nthBit16Left(u16 val, u16 nth) { return (val << (nth - 1)) & 1; }
// Returns the nth bit of a 8 bit integer from the left
// @param val The integer to be evaluated
// @param nth The bit index from the right (1 indexed)
// @return The value of the retrieved bit
forceinline bool nthBit8Left(u8 val, u8 nth) { return (val << (nth - 1)) & 1; }
