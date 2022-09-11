#pragma once

#include <cstddef>
#include "preprocessor.h"

// Workarounds to meet newer standards

#ifdef Override
#define override
#define static_assert(condition, ...) typedef int TOKENPASTE2(static_assert_, __LINE__)[(condition) ? 1 : -1]
#define forceinline __attribute__((always_inline))
#else
#define static_assert(x, ...)
#define forceinline
#endif

#define packed      __attribute__((packed))
#define aligned(x)  __attribute__((aligned(x)))

#define nullptr NULL

#define ENUM_CLASS(name, ...)              \
    class name {virtual void This_error_means_you_forgot_to_write___type___in_an_object_instanciation()=0;public: \
        enum __type__ { __VA_ARGS__ };     \
    }

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
#include "utils/rect.h"
