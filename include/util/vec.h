#pragma once

#include "types.h"

template <typename T>
struct Vec2 { // size: 0x8
    T x;  // _0
    T y;  // _4

    inline Vec2(T val = 0) :
        x(val), y(val) { }
    inline Vec2(T x, T y) :
        x(x), y(y) { }
    
    Vec2 operator+(const Vec2& other) const { Vec2 result; add(result, *this, other); return result; }
    Vec2& operator+=(const Vec2& other) { add(*this, *this, other); return *this; }

    Vec2 operator-(const Vec2& other) const { Vec2 result; sub(result, *this, other); return result; }
    Vec2& operator-=(const Vec2& other) { sub(*this, *this, other); return *this; }

    Vec2 operator*(const T val) const { Vec2 result; scale(result, *this, val); return result; }
    Vec2& operator*=(const T val) { scale(*this, *this, val); return *this; }

    Vec2 operator/(const T val) const { return operator*(1 / val); }
    Vec2& operator/=(const T val) { return operator*=(1 / val); }

private:
    static inline Vec2& add(Vec2& out, const Vec2& a, const Vec2& b) {
        out.x = a.x + b.x;
        out.y = a.y + b.y;
        return out;
    }

    static inline Vec2& sub(Vec2& out, const Vec2& a, const Vec2& b) {
        out.x = a.x - b.x;
        out.y = a.y - b.y;
        return out;
    }

    static inline Vec2& scale(Vec2& out, const Vec2& vec, const T scale) {
        out.x = vec.x * scale;
        out.y = vec.y * scale;
        return out;
    }
};

typedef Vec2<f32> Vec2f;
typedef Vec2<u32> Vec2u;
typedef Vec2<s32> Vec2i;

template <typename T>
struct Vec3 { // size: 0xC
    T x;  // _0
    T y;  // _4
    T z;  // _8

    inline Vec3(T val = 0) :
        x(val), y(val), z(val) { }
    inline Vec3(T x, T y, T z) :
        x(x), y(y), z(z) { }
    inline Vec3(const Vec2<T>& vec) :
        x(vec.x), y(vec.y), z(0) { }
    
    Vec3 operator+(const Vec3& other) const { Vec3 result; add(result, *this, other); return result; }
    Vec3& operator+=(const Vec3& other) { add(*this, *this, other); return *this; }

    Vec3 operator-(const Vec3& other) const { Vec3 result; sub(result, *this, other); return result; }
    Vec3& operator-=(const Vec3& other) { sub(*this, *this, other); return *this; }

    Vec3 operator*(const T val) const { Vec3 result; scale(result, *this, val); return result; }
    Vec3& operator*=(const T val) { scale(*this, *this, val); return *this; }

    Vec3 operator/(const T val) const { return operator*(1 / val); }
    Vec3& operator/=(const T val) { return operator*=(1 / val); }

private:
    static inline Vec3& add(Vec3& out, const Vec3& a, const Vec3& b) {
        out.x = a.x + b.x;
        out.y = a.y + b.y;
        out.z = a.z + b.z;
        return out;
    }

    static inline Vec3& sub(Vec3& out, const Vec3& a, const Vec3& b) {
        out.x = a.x - b.x;
        out.y = a.y - b.y;
        out.z = a.y - b.z;
        return out;
    }

    static inline Vec3& scale(Vec3& out, const Vec3& vec, const T scale) {
        out.x = vec.x * scale;
        out.y = vec.y * scale;
        out.z = vec.z * scale;
        return out;
    }
};

typedef Vec3<f32> Vec3f;
typedef Vec3<u32> Vec3u;
typedef Vec3<s32> Vec3i;
