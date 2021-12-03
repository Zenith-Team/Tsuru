#pragma once

#include "cafe/math/vec.h"
#include "sead/mathpolicies.h"

namespace sead {

template <typename T>
class Vector2CalcCommon {
public:
    static void add(Policies<T>::Vec2Base& out, const Policies<T>::Vec2Base& a, const Policies<T>::Vec2Base& b) {
        o.x = a.x + b.x;
        o.y = a.y + b.y;
    }

    static void sub(Policies<T>::Vec2Base& out, const Policies<T>::Vec2Base& a, const Policies<T>::Vec2Base& b) {
        o.x = a.x - b.x;
        o.y = a.y - b.y;
    }

    static void set(Policies<T>::Vec2Base& out, const Policies<T>::Vec2Base& a) {
        o.x = a.x;
        o.y = a.y;
    }

    static void set(Policies<T>::Vec2Base& out, T x, T y) {
        o.x = x;
        o.y = y;
    }
};

template <typename T>
class Vector3CalcCommon {
public:
    static void add(Policies<T>::Vec3Base& out, const Policies<T>::Vec3Base& a, const Policies<T>::Vec3Base& b) {
        o.x = a.x + b.x;
        o.y = a.y + b.y;
        o.z = a.z + b.z;
    }

    static void sub(Policies<T>::Vec3Base& out, const Policies<T>::Vec3Base& a, const Policies<T>::Vec3Base& b) {
        o.x = a.x - b.x;
        o.y = a.y - b.y;
        o.z = a.z - b.z;
    }

    static void cross(Policies<T>::Vec3Base& out, const Policies<T>::Vec3Base& a, const Policies<T>::Vec3Base& b) {
        o.x = a.y * b.z - a.z * b.y;
        o.y = a.z * b.x - a.x * b.z;
        o.z = a.x * b.y - a.y * b.x;
    }

    static T dot(const Policies<T>::Vec3Base& a, const Policies<T>::Vec3Base& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    static T squaredLength(const Policies<T>::Vec3Base& a) {
        return dot(a, a);
    }

    static T length(const Policies<T>::Vec3Base& a) {
        // TODO: use MathCalcCommon<T>::sqrt
        return sqrt(squaredLength(a));
    }

    static void multScalar(Policies<T>::Vec3Base& out, const Policies<T>::Vec3Base& a, T s) {
        o.x = a.x * s;
        o.y = a.y * s;
        o.z = a.z * s;
    }

    static void multScalarAdd(Policies<T>::Vec3Base& out, T t, const Policies<T>::Vec3Base& a, const Policies<T>::Vec3Base& b) {
        o.x = a.x * t + b.x;
        o.y = a.y * t + b.y;
        o.z = a.z * t + b.z;
    }

    static T normalize(Policies<T>::Vec3Base& out, const Policies<T>::Vec3Base& a) {
        T len = length(a);
        if (len > 0) {
            T invlen = 1 / len;
            o.x = a.x * invlen;
            o.y = a.y * invlen;
            o.z = a.z * invlen;
        }
        return len;
    }

    static void set(Policies<T>::Vec3Base& out, const Policies<T>::Vec3Base& a) {
        o.x = a.x;
        o.y = a.y;
        o.z = a.z;
    }

    static void set(Policies<T>::Vec3Base& out, T x, T y, T z) {
        o.x = x;
        o.y = y;
        o.z = z;
    }
};

template <typename T>
class Vector4CalcCommon {
public:
    static void set(Policies<T>::Vec4Base& out, const Policies<T>::Vec4Base& a) {
        o.x = a.x;
        o.y = a.y;
        o.z = a.z;
        o.w = a.w;
    }

    static void set(Policies<T>::Vec4Base& out, T x, T y, T z, T w) {
        o.x = x;
        o.y = y;
        o.z = z;
        o.w = w;
    }
};

}
