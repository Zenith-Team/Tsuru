#pragma once

#include <types.h>

#define M_E         2.718281828459045235360
#define M_LOG2E	    1.442695040888963407
#define M_LOG10E    0.434294481903251827651
#define M_LN2       0.69314718055994530942
#define M_LN10      2.30258509299404568402
#define M_2PI       6.28318530717958647692
#define M_PI        3.14159265358979323846
#define M_PI_2      1.570796326794896619231
#define M_PI_4      0.785398163397448309616
#define M_1_PI      0.318309886183790671538
#define M_2_PI      0.636619772367581343076
#define M_2_SQRTPI  1.12837916709551257390
#define M_SQRT2     1.41421356237309504880
#define M_SQRT1_2   0.7071067811865476

extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 tanf(f32 x);
extern f32 asinf(f32 x);
extern f32 acosf(f32 x);
extern f32 atan2f(f32 x, f32 y);
extern f32 expf(f32 x);
extern f32 logf(f32 x);
extern f32 powf(f32 x, f32 y);
extern f32 sqrtf(f32 x);
extern f32 fmodf(f32 x, f32 y);

inline f32 pow2f(f32 x) {
    return x * x;
}

inline f32 fabsf(f32 x) {
    return (x < 0.0f) ? -x : x;
}

inline f32 degToRad(f32 deg) {
    return (deg * M_PI) / 180.0f;
}

inline f32 radToDeg(f32 rad) {
    return (rad * 180.0f) / M_PI;
}

inline u32 fixRad(f32 val) {
    val = fmodf(val, M_2PI);
    if (val < 0.0f) val += M_2PI;
    return val * 683565276;
}

inline f32 unfixRad(u32 val) {
    return val / 683565248.0f;
}

inline u32 fixDeg(f32 val) {
    val = fmodf(val, 360.0f);
    if (val < 0.0f) val += 360.0f;
    return val * 11930465.0f;
}

inline f32 unfixDef(u32 val) {
    return (val / 11930465.0f);
}

template <class T>
const T& min(const T& x, const T& y) {
    return !(y < x) ? x : y;
}

template <class T>
const T& max(const T& x, const T& y) {
    return (x < y) ? y : x;
}
