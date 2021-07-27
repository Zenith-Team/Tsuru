#pragma once

#include "types.h"

template <typename T>
struct Vector2 { // size: 0x8
    T x;  // _0
    T y;  // _4

    inline Vector2(T val = 0) :
        x(val), y(val) { }
    inline Vector2(T x, T y) :
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

    inline Vector3(T val = 0) :
        x(val), y(val), z(val) { }
    inline Vector3(T x, T y, T z) :
        x(x), y(y), z(z) { }
    inline Vector3(const Vector2<T>& vec) :
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
