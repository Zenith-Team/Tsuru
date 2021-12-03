#pragma once

#include "sead/mathpolicies.h"
#include "types.h"
#include "sead/vectorcalccommon.h"

namespace sead {

template <typename T>
class Vector2 : public Policies<T>::Vec2Base {
public:
    Vector2()
        : x(0)
        , y(0)
    { }

    Vector2(T v)
        : x(v)
        , y(v)
    { }

    Vector2(T x, T y)
        : x(x)
        , y(y)
    { }

    Vector2(const Vector2& other)
        : x(other.x)
        , y(other.y)
    { }

    void set(const Vector2& other) {
        Vector2CalcCommon<T>::set(*this, other);
    }

    void set(T x, T y) {
        Vector2CalcCommon<T>::set(*this, x, y);
    }

    Vector2<T> operator+(const Vector2<T>& other) const {
        Vector2<T> result;
        Vector2CalcCommon<T>::add(result, *this, other);
        return result;
    }

    Vector2<T> operator-(const Vector2<T>& other) const {
        Vector2<T> result;
        Vector2CalcCommon<T>::sub(result, *this, other);
        return result;
    }

    Vector2<T> operator+=(const Vector2<T>& other) {
        Vector2CalcCommon<T>::add(*this, *this, other);
        return *this;
    }

    Vector2<T> operator-=(const Vector2<T>& other) {
        Vector2CalcCommon<T>::sub(*this, *this, other);
        return *this;
    }

    Vector2<T> operator=(const Vector2<T>& other) {
        Vector2CalcCommon<T>::set(*this, other);
        return *this;
    }

    Vector2<T> operator==(const Vector2<T>& other) const {
        return this->x == other.x && this->y == other.y;
    }

    static const Vector2 zero;
    static const Vector2 ex;
    static const Vector2 ey;
    static const Vector2 one;
};

template <typename T>
class Vector3 : public Policies<T>::Vec3Base {
public:
    Vector3()
        : x(0)
        , y(0)
        , z(0)
    { }

    Vector3(T v)
        : x(v)
        , y(v)
        , z(v)
    { }

    Vector3(T x, T y, T z)
        : x(x)
        , y(y)
        , z(z)
    { }

    Vector3(const Vector3& other)
        : x(other.x)
        , y(other.y)
        , z(other.z)
    { }

    Vector3(const Vector2<T>& other)
        : x(other.x)
        , y(other.y)
        , z(0)
    { }

    void set(const Vector3& other) {
        Vector3CalcCommon<T>::set(*this, other);
    }

    void set(T x, T y, T z) {
        Vector3CalcCommon<T>::set(*this, x, y, z);
    }

    Vector3<T> operator+(const Vector3<T>& other) const {
        Vector3<T> result;
        Vector3CalcCommon<T>::add(result, *this, other);
        return result;
    }

    Vector3<T> operator-(const Vector3<T>& other) const {
        Vector3<T> result;
        Vector3CalcCommon<T>::sub(result, *this, other);
        return result;
    }

    Vector3<T> operator+=(const Vector3<T>& other) {
        Vector3CalcCommon<T>::add(*this, *this, other);
        return *this;
    }

    Vector3<T> operator-=(const Vector3<T>& other) {
        Vector3CalcCommon<T>::sub(*this, *this, other);
        return *this;
    }

    Vector3<T> operator=(const Vector3<T>& other) {
        Vector3CalcCommon<T>::set(*this, other);
        return *this;
    }

    Vector3<T> operator==(const Vector3<T>& other) const {
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }

    static const Vector3 zero;
    static const Vector3 ex;
    static const Vector3 ey;
    static const Vector3 ez;
    static const Vector3 one;
};

template <typename T>
class Vector4 : public Policies<T>::Vec4Base {
public:
    Vector4()
        : x(0)
        , y(0)
        , z(0)
        , w(0)
    { }

    Vector4(T v)
        : x(v)
        , y(v)
        , z(v)
        , w(v)
    { }

    Vector4(T x, T y, T z, T w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    { }

    Vector4(const Vector4& other)
        : x(other.x)
        , y(other.y)
        , z(other.z)
        , w(other.w)
    { }

    void set(const Vector4& other) {
        
    }

    void set(T x, T y, T z, T w) {
        
    }

    static const Vector4 zero;
    static const Vector4 ex;
    static const Vector4 ey;
    static const Vector4 ez;
    static const Vector4 ew;
    static const Vector4 one;
};

typedef Vector2<s32> Vec2i;
typedef Vector2<u32> Vec2u;
typedef Vector2<f32> Vec2f;
typedef Vector2<f64> Vec2d;

typedef Vector3<s32> Vec3i;
typedef Vector3<u32> Vec3u;
typedef Vector3<f32> Vec3f;
typedef Vector3<f64> Vec3d;

typedef Vector4<s32> Vec4i;
typedef Vector4<u32> Vec4u;
typedef Vector4<f32> Vec4f;


}
