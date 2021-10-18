#pragma once

#include <cstddef>
#include <preprocessor.h>

// Workarounds to meet newer standards

//! This is a hack, if you got here because of an error:
//* To have override intellisense: Add \t-DOverride above \t-DCemu on compiler_cemu.py
//? To just compile without override intellisense, uncomment #define below.
//#define Override
#ifdef Override
#define override
#endif

#define forceinline __attribute__((always_inline))
#define packed      __attribute__((packed))
#define aligned(x)  __attribute__((aligned(x)))

#define nullptr NULL
#define static_assert(condition, ...) typedef int TOKENPASTE2(static_assert_, __LINE__)[(condition) ? 1 : -1]

// Primitive type shortcuts

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

typedef volatile u8         vu8;
typedef volatile u16       vu16;
typedef volatile u32       vu32;
typedef volatile u64       vu64;

typedef volatile s8         vs8;
typedef volatile s16       vs16;
typedef volatile s32       vs32;
typedef volatile s64       vs64;

typedef volatile f32       vf32;
typedef volatile f64       vf64;

typedef unsigned int     size_t;
typedef signed int      ssize_t;

typedef unsigned int  uintptr_t;
typedef signed int     intptr_t;

typedef void       (*funcPtr)();

// Utility types

#include <utils/vec.h>
#include <utils/mtx.h>
#include <utils/rect.h>
