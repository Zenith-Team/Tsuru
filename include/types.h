#pragma once

// Workarounds to match newer standards
#define nullptr NULL
#define override
#define forceinline __attribute__((always_inline))

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;

typedef signed char         s8;
typedef signed short        s16;
typedef signed int          s32;
typedef signed long long    s64;

typedef float               f32;
typedef double              f64;

typedef unsigned int        size_t;
typedef signed int          ssize_t;

typedef unsigned int        uintptr_t;
typedef signed int          intptr_t;

enum Direction
{
    RIGHT = 0,
    LEFT  = 1,
    UP    = 2,
    DOWN  = 3
};

