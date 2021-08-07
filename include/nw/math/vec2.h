#pragma once

#include <math.h>

namespace nw { namespace math {

struct VEC2 {
    static const VEC2& Zero() {
        static const VEC2 zero = (VEC2){ 0.0f, 0.0f };
        return zero;
    }

    f32 MagnitudeSquare() const {
        return x*x + y*y;
    }

    f32 Magnitude() const {
        return sqrtf(MagnitudeSquare());
    }

    void Normalize() {
        f32 invMag = 1.0f / Magnitude();
        x *= invMag;
        y *= invMag;
    }

    f32 x;
    f32 y;


};

inline VEC2& operator+=(VEC2& lhs, const VEC2& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
inline VEC2 operator+(const VEC2& lhs, const VEC2& rhs) { VEC2 ret = lhs; return (ret += rhs); }

inline VEC2& operator-=(VEC2& lhs, const VEC2& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }
inline VEC2 operator-(const VEC2& lhs, const VEC2& rhs) { VEC2 ret = lhs; return (ret -= rhs); }

inline VEC2& operator*=(VEC2& lhs, f32 a) { lhs.x *= a; lhs.y *= a; return lhs; }
inline VEC2 operator*(const VEC2& lhs, f32 a) { VEC2 ret = lhs; return (ret *= a); }
inline VEC2 operator*(f32 a, const VEC2& rhs) { return (VEC2){ a * rhs.x, a * rhs.y }; }

} }
