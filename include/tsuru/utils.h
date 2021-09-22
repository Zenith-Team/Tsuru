#pragma once

#include <types.h>

// Compare if two strings are equal
extern "C" int strcmp(const char* str1, const char* str2);

// Compare if two wide strings are equal
extern "C" int wcscmp(const wchar_t* str1, const wchar_t* str2);

// Modified version of moveValueTo which supports overflowing/underflowing the value, used for smooth rotations.
bool moveValueWithOverflowTo(u32 &value, u32 target, u32 step, bool subtract);
