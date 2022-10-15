#pragma once

#include "types.h"
#include "sead/mathpolicies.h"
#include "math/functions.h"

//* Full disclosure: A significant portion of this is not from actual sead and I added it myself because sead vectors are heavily lacking for my purposes.
//* If you want an accurate sead header, go to https://github.dev/aboood40091/sead/

namespace sead {

template <typename T>
class Vector2 : public Policies<T>::Vec2Base {
public:
    typedef T ValueType;

    Vector2() {
        this->x = 0;
        this->y = 0;
    }

    Vector2(const T val) {
        this->x = val;
        this->y = val;
    }

    Vector2(const T x, const T y) {
        this->x = x;
        this->y = y;
    }

    Vector2(const Vector2<T>& other) {
        this->x = other.x;
        this->y = other.y;
    }

    T lengthSquared() const {
        return this->x * this->x + this->y * this->y;
    }

    T length() const {
        return sqrtf(this->lengthSquared());
    }

    T distanceTo(const Vector2<T>& other) const {
        return (*this - other).length();
    }

    void normalize() {
        const T len = this->length();
        this->x /= len;
        this->y /= len;
    }

    Vector2<T> normalized() const {
        const T len = this->length();
        return Vector2<T>(this->x / len, this->y / len);
    }

    Vector2<T>& lerp(const Vector2<T>& other, const T t) {
        this->x = (1 - t) * this->x + t * other.x;
        this->y = (1 - t) * this->y + t * other.y;
        return *this;
    }

    Vector2<T> operator+(const Vector2<T>& other) const { return Vector2<T>(this->x + other.x, this->y + other.y); }
    Vector2<T> operator+(const T other) const { return Vector2<T>(this->x + other, this->y + other); }

    Vector2<T> operator-(const Vector2<T>& other) const { return Vector2<T>(this->x - other.x, this->y - other.y); }
    Vector2<T> operator-(const T other) const { return Vector2<T>(this->x - other, this->y - other); }

    Vector2<T> operator*(const Vector2<T>& other) const { return Vector2<T>(this->x * other.x, this->y * other.y); }
    Vector2<T> operator*(const T other) const { return Vector2<T>(this->x * other, this->y * other); }

    Vector2<T> operator/(const Vector2<T>& other) const { return Vector2<T>(this->x / other.x, this->y / other.y); }
    Vector2<T> operator/(const T other) const { return Vector2<T>(this->x / other, this->y / other); }

    Vector2<T> operator-() const { return Vector2<T>(-this->x, -this->y); }

    Vector2<T>& operator+=(const Vector2<T>& other) { this->x += other.x; this->y += other.y; return *this; }
    Vector2<T>& operator+=(const T other) { this->x += other; this->y += other; return *this; }
    Vector2<T>& operator++() { this->x++; this->y++; return *this; }
    Vector2<T> operator++(int) { Vector2<T> tmp(*this); this->x++; this->y++; return tmp; }

    Vector2<T>& operator-=(const Vector2<T>& other) { this->x -= other.x; this->y -= other.y; return *this; }
    Vector2<T>& operator-=(const T other) { this->x -= other; this->y -= other; return *this; }
    Vector2<T>& operator--() { this->x--; this->y--; return *this; }
    Vector2<T> operator--(int) { Vector2<T> tmp(*this); this->x--; this->y--; return tmp; }

    Vector2<T>& operator*=(const Vector2<T>& other) { this->x *= other.x; this->y *= other.y; return *this; }
    Vector2<T>& operator*=(const T other) { this->x *= other; this->y *= other; return *this; }

    Vector2<T>& operator/=(const Vector2<T>& other) { this->x /= other.x; this->y /= other.y; return *this; }
    Vector2<T>& operator/=(const T other) { this->x /= other; this->y /= other; return *this; }

    Vector2<T>& operator=(const Vector2<T>& other) { this->x = other.x; this->y = other.y; return *this; }
    Vector2<T>& operator=(const T other) { this->x = other; this->y = other; return *this; }

    bool operator==(const Vector2<T>& other) const { return this->x == other.x && this->y == other.y; }
    bool operator==(const T other) const { return this->x == other && this->y == other; }

    bool operator!=(const Vector2<T>& other) const { return this->x != other.x || this->y != other.y; }
    bool operator!=(const T other) const { return this->x != other || this->y != other; }
};

template <typename T>
class Vector3 : public Policies<T>::Vec3Base {
public:
    typedef T ValueType;

    Vector3() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    Vector3(const T val) {
        this->x = val;
        this->y = val;
        this->z = val;
    }

    Vector3(const T x, const T y, const T z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3(const T x, const T y) {
        this->x = x;
        this->y = y;
        this->z = 0;
    }

    Vector3(const Vector3<T>& other) {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
    }

    Vector3(const Vector2<T>& other) {
        this->x = other.x;
        this->y = other.y;
        this->z = 0;
    }

    T lengthSquared() const {
        return this->x * this->x + this->y * this->y + this->z * this->z;
    }

    T length() const {
        return sqrtf(this->lengthSquared());
    }

    T distanceTo(const Vector3<T>& other) const {
        return (*this - other).length();
    }

    void normalize() {
        const T len = this->length();
        this->x /= len;
        this->y /= len;
        this->z /= len;
    }

    Vector3<T> normalized() const {
        const T len = this->length();
        return Vector3<T>(this->x / len, this->y / len, this->z / len);
    }

    Vector3<T>& lerp(const Vector3<T>& other, const T t) {
        this->x = (1 - t) * this->x + t * other.x;
        this->y = (1 - t) * this->y + t * other.y;
        this->z = (1 - t) * this->z + t * other.z;
        return *this;
    }

    Vector3<T> crossedWith(const Vector3<T>& other) const {
        return Vector3<T>(this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z, this->x * other.y - this->y * other.x);
    }

    Vector3<T>& crossWith(const Vector3<T>& other) {
        *this = this->crossedWith(other);
    }

    Vector3<T> operator+(const Vector3<T>& other) const { return Vector3<T>(this->x + other.x, this->y + other.y, this->z + other.z); }
    Vector3<T> operator+(const T other) const { return Vector3<T>(this->x + other, this->y + other, this->z + other); }

    Vector3<T> operator-(const Vector3<T>& other) const { return Vector3<T>(this->x - other.x, this->y - other.y, this->z - other.z); }
    Vector3<T> operator-(const T other) const { return Vector3<T>(this->x - other, this->y - other, this->z - other); }

    Vector3<T> operator*(const Vector3<T>& other) const { return Vector3<T>(this->x * other.x, this->y * other.y, this->z * other.z); }
    Vector3<T> operator*(const T other) const { return Vector3<T>(this->x * other, this->y * other, this->z * other); }

    Vector3<T> operator/(const Vector3<T>& other) const { return Vector3<T>(this->x / other.x, this->y / other.y, this->z / other.z); }
    Vector3<T> operator/(const T other) const { return Vector3<T>(this->x / other, this->y / other, this->z / other); }

    Vector3<T> operator-() const { return Vector3<T>(-this->x, -this->y, -this->z); }

    Vector3<T>& operator+=(const Vector3<T>& other) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
    Vector3<T>& operator+=(const T other) { this->x += other; this->y += other; this->z += other; return *this; }
    Vector3<T>& operator++() { this->x++; this->y++; this->z++; return *this; }
    Vector3<T> operator++(int) { Vector3<T> tmp(*this); this->x++; this->y++; this->z++; return tmp; }

    Vector3<T>& operator-=(const Vector3<T>& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; return *this; }
    Vector3<T>& operator-=(const T other) { this->x -= other; this->y -= other; this->z -= other; return *this; }
    Vector3<T>& operator--() { this->x--; this->y--; this->z--; return *this; }
    Vector3<T> operator--(int) { Vector3<T> tmp(*this); this->x--; this->y--; this->z--; return tmp; }

    Vector3<T>& operator*=(const Vector3<T>& other) { this->x *= other.x; this->y *= other.y; this->z *= other.z; return *this; }
    Vector3<T>& operator*=(const T other) { this->x *= other; this->y *= other; this->z *= other; return *this; }

    Vector3<T>& operator/=(const Vector3<T>& other) { this->x /= other.x; this->y /= other.y; this->z /= other.z; return *this; }
    Vector3<T>& operator/=(const T other) { this->x /= other; this->y /= other; this->z /= other; return *this; }

    Vector3<T>& operator=(const Vector3<T>& other) { this->x = other.x; this->y = other.y; this->z = other.z; return *this; }
    Vector3<T>& operator=(const T other) { this->x = other; this->y = other; this->z = other; return *this; }

    bool operator==(const Vector3<T>& other) const { return this->x == other.x && this->y == other.y && this->z == other.z; }
    bool operator==(const T other) const { return this->x == other && this->y == other && this->z == other; }

    bool operator!=(const Vector3<T>& other) const { return this->x != other.x || this->y != other.y || this->z != other.z; }
    bool operator!=(const T other) const { return this->x != other || this->y != other || this->z != other; }
};

template <typename T>
class Vector4 : public Policies<T>::Vec4Base {
public:
    typedef T ValueType;
};

}

typedef sead::Vector2<f32> Vec2f;
typedef sead::Vector2<f64> Vec2d;
typedef sead::Vector2<s32> Vec2i;
typedef sead::Vector2<u32> Vec2u;

typedef sead::Vector3<f32> Vec3f;
typedef sead::Vector3<f64> Vec3d;
typedef sead::Vector3<s32> Vec3i;
typedef sead::Vector3<u32> Vec3u;
