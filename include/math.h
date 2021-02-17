#pragma once

#include "types.h"

#define M_E             2.718281828459045235360
#define M_LOG2E	        1.442695040888963407
#define M_LOG10E        0.434294481903251827651
#define M_LN2           0.69314718055994530942
#define M_LN10          2.30258509299404568402
#define M_2PI           6.28318530717958647692
#define M_PI            3.14159265358979323846
#define M_PI_2          1.570796326794896619231
#define M_PI_4          0.785398163397448309616
#define M_1_PI          0.318309886183790671538
#define M_2_PI          0.636619772367581343076
#define M_2_SQRTPI      1.12837916709551257390
#define M_SQRT2         1.41421356237309504880
#define M_SQRT1_2       0.7071067811865476

f32 sin(f32 x);
f32 cos(f32 x);
f32 tan(f32 x);
f32 asin(f32 x);
f32 acos(f32 x);
f32 atan2(f32 x, f32 y);

f32 exp(f32 x);
f32 log(f32 x);
f32 pow(f32 x, f32 y);
f32 sqrt(f32 a);

inline f32 pow2(f32 x) { return x * x; }

inline f32 fabs(f32 x) { return (x < 0.0f) ? -x : x; }
f32 fmod(f32 a, f32 b);

template <class T>
const T& min(const T& a, const T& b) { return !(b<a) ? a : b; }

template <class T>
const T& max(const T& a, const T& b) { return (a<b) ? b : a; }


inline f32 deg_to_rad(f32 deg)
{
    return (deg * M_PI) / 180.0f;
}

inline f32 rad_to_deg(f32 rad)
{
    return (rad * 180.0f) / M_PI;
}


inline u32 fix_rad(f32 val)
{
    val = fmod(val, M_2PI);
    if (val < 0.0f) val += M_2PI;
    return val * 683565276;
}

inline f32 unfix_rad(u32 val)
{
    return val / 683565248.0f;
}


inline u32 fix_deg(f32 val)
{
    val = fmod(val, 360.0f);
    if (val < 0.0f) val += 360.0f;
    return val * 11930465.0f;
}

inline f32 unfix_deg(u32 val)
{
    return (val / 11930465.0f);
}
