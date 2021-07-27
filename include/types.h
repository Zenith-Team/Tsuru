#pragma once

#include <cstddef>
#include "preprocessor.h"

// Workarounds to meet newer standards

#define nullptr NULL
#define override
#define forceinline __attribute__((always_inline))
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

typedef unsigned int       size_t;
typedef signed int         ssize_t;

typedef unsigned int       uintptr_t;
typedef signed int         intptr_t;


// Basic utility types

template <typename T>
struct Vector2 { // size: 0x8
    T x;  // _0
    T y;  // _4

    Vector2(T val = 0) :
        x(val), y(val) { }
    Vector2(T x, T y) :
        x(x), y(y) { }
    
    Vector2 operator+(const Vector2& other) const { Vector2 result; add(result, *this, other); return result; }
    Vector2& operator+=(const Vector2& other) { add(*this, *this, other); return *this; }

    Vector2 operator-(const Vector2& other) const { Vector2 result; sub(result, *this, other); return result; }
    Vector2& operator-=(const Vector2& other) { sub(*this, *this, other); return *this; }

    Vector2 operator*(const T val) const { Vector2 result; scale(result, *this, val); return result; }
    Vector2& operator*=(const T val) { scale(*this, *this, val); return *this; }

    Vector2 operator/(const T val) const { return operator*(1 / val); }
    Vector2& operator/=(const T val) { return operator*=(1 / val); }

private:
    static inline Vector2& add(Vector2& out, const Vector2& a, const Vector2& b) {
        out.x = a.x + b.x;
        out.y = a.y + b.y;
        return out;
    }

    static inline Vector2& sub(Vector2& out, const Vector2& a, const Vector2& b) {
        out.x = a.x - b.x;
        out.y = a.y - b.y;
        return out;
    }

    static inline Vector2& scale(Vector2& out, const Vector2& vec, const T scale) {
        out.x = vec.x * scale;
        out.y = vec.y * scale;
        return out;
    }
};

typedef Vector2<f32> Vec2f;
typedef Vector2<u32> Vec2u;
typedef Vector2<s32> Vec2i;

template <typename T>
struct Vector3 { // size: 0xC
    T x;  // _0
    T y;  // _4
    T z;  // _8

    Vector3(T val = 0) :
        x(val), y(val), z(val) { }
    Vector3(T x, T y, T z) :
        x(x), y(y), z(z) { }
    Vector3(const Vector2<T>& vec) :
        x(vec.x), y(vec.y), z(0) { }
    
    Vector3 operator+(const Vector3& other) const { Vector3 result; add(result, *this, other); return result; }
    Vector3& operator+=(const Vector3& other) { add(*this, *this, other); return *this; }

    Vector3 operator-(const Vector3& other) const { Vector3 result; sub(result, *this, other); return result; }
    Vector3& operator-=(const Vector3& other) { sub(*this, *this, other); return *this; }

    Vector3 operator*(const T val) const { Vector3 result; scale(result, *this, val); return result; }
    Vector3& operator*=(const T val) { scale(*this, *this, val); return *this; }

    Vector3 operator/(const T val) const { return operator*(1 / val); }
    Vector3& operator/=(const T val) { return operator*=(1 / val); }

private:
    static inline Vector3& add(Vector3& out, const Vector3& a, const Vector3& b) {
        out.x = a.x + b.x;
        out.y = a.y + b.y;
        out.z = a.z + b.z;
        return out;
    }

    static inline Vector3& sub(Vector3& out, const Vector3& a, const Vector3& b) {
        out.x = a.x - b.x;
        out.y = a.y - b.y;
        out.z = a.y - b.z;
        return out;
    }

    static inline Vector3& scale(Vector3& out, const Vector3& vec, const T scale) {
        out.x = vec.x * scale;
        out.y = vec.y * scale;
        out.z = vec.z * scale;
        return out;
    }
};

typedef Vector3<f32> Vec3f;
typedef Vector3<u32> Vec3u;
typedef Vector3<s32> Vec3i;

struct Rect { // size: 0x10
    static Rect sZero;

    f32 left;       // _0
    f32 bottom;     // _4
    f32 right;      // _8
    f32 top;        // _C
};
