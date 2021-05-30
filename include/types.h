#pragma once

#define __DEBUG 1
#define nullptr NULL
#define override
#define deleted
#define forceinline __attribute__((always_inline))

// https://stackoverflow.com/a/1597129
#define TOKENPASTE(x, y) x ## y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)

#define static_assert(condition, ...) typedef int TOKENPASTE2(static_assert_, __LINE__)[(condition) ? 1 : -1]

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

namespace Direction { enum Direction {
    Right = 0,
    Left  = 1,
    Up    = 2,
    Down  = 3
};
}

