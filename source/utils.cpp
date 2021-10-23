// Misc. utility C++ functions

#include <types.h>

// Compare if two wide strings are equal
extern "C" s32 wcscmp(const wchar_t* str1, const wchar_t* str2) {
    while (*str1 == *str2++)
        if (*str1++ == 0)
            return 0;

    return (*str1 - *--str2);
}

// Modified version of moveValueTo which supports overflowing/underflowing the value, used for smooth rotations.
bool moveValueWithOverflowTo(u32& value, u32 target, u32 step, bool subtract) {
    u32 counter = 0;
    u32 startValue = value;
    s64 offset = target - startValue;
    if (offset < 0) offset *= -1;

    if (counter + step < offset) {
        if (!subtract) value += step;
        else value -= step;
        counter += step;
        return false;
    }

    value = target;
    return true;
}

// Inline function static implementation for branching to from asm

bool nthBitRight(u32 val, u32 nth) {
    return (val >> (nth - 1)) & 1;
}

bool nthBitLeft(u32 val, u32 nth) {
    return (val << (nth - 1)) & 1;
}
