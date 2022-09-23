#pragma once

#include "types.h"
#include "sead/safestring.h"
#include "math/functions.h"

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


static inline bool nthBit64Right(u64 val, u64 nth) { return (val >> (nth - 1)) & 1; }
static inline bool nthBit32Right(u32 val, u32 nth) { return (val >> (nth - 1)) & 1; }
static inline bool nthBit16Right(u16 val, u16 nth) { return (val >> (nth - 1)) & 1; }
static inline bool nthBit8Right(u8 val, u8 nth) { return (val >> (nth - 1)) & 1; }


static inline bool nthBit64Left(u64 val, u64 nth) { return (val << (nth - 1)) & 1; }
static inline bool nthBit32Left(u32 val, u32 nth) { return (val << (nth - 1)) & 1; }
static inline bool nthBit16Left(u16 val, u16 nth) { return (val << (nth - 1)) & 1; }
static inline bool nthBit8Left(u8 val, u8 nth) { return (val << (nth - 1)) & 1; }

template <typename T>
static inline void swap(T& a, T& b) {
    const T temp = a;
    a = b;
    b = temp;
}

static inline const char* formatBool(bool value) {
    return value ? "true" : "false";
}

// Converts an integer to a string of it's binary representation
// @param num The integer to be converted
template <typename T>
static inline sead::SafeString toBinaryString(T num) {
    u8 bits = sizeof(T) * 8;
    char str[65];
    for (u8 c = 0; c < bits; c++) {
        bool one = (num & (static_cast<T>(1) << ((bits - 1) - c))) != 0;
        str[c] = one ? '1' : '0';
    }
    str[bits] = '\0';
    return sead::SafeString(str);
}

// Parses a string of binary digits into an integer
// @param str The string to be parsed
template <typename T>
static inline T parseBinaryString(const char* str) {
    u8 bits = sizeof(T) * 8;
    u64 n = 0;
    for (u8 c = 0; c < bits; c++) {
        if (str[(bits - 1) - c] == '1') {
            n += powi(static_cast<T>(2), static_cast<T>(c));
        }
    }
    return static_cast<T>(n);
}

// Returns the number of bits set to 1 in an integer
// @param x The integer to be evaluated
template <typename T>
static inline u8 popcount(T x) {
    u8 c = 0;
    for (; x != 0; x &= x - 1) c++;
    return c;
}

template <typename T>
static inline void toggle(T& val) {
    val = !val;
}
