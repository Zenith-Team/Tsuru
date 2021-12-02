#pragma once

#include "dynlibs/os/functions.h"

#include "sead/math/seadMathCalcCommon.h"

namespace sead {

template <typename T>
inline void
Vector2CalcCommon<T>::add(Base& o, const Base& a, const Base& b)
{
    o.x = a.x + b.x;
    o.y = a.y + b.y;
}

template <typename T>
inline void
Vector2CalcCommon<T>::sub(Base& o, const Base& a, const Base& b)
{
    o.x = a.x - b.x;
    o.y = a.y - b.y;
}

template <typename T>
inline void
Vector2CalcCommon<T>::set(Base& o, const Base& v)
{
    o.x = v.x;
    o.y = v.y;
}

template <typename T>
inline void
Vector2CalcCommon<T>::set(Base& v, T x, T y)
{
    v.x = x;
    v.y = y;
}

template <typename T>
inline void
Vector3CalcCommon<T>::add(Base& o, const Base& a, const Base& b)
{
    o.x = a.x + b.x;
    o.y = a.y + b.y;
    o.z = a.z + b.z;
}

template <>
inline void
Vector3CalcCommon<f32>::add(Base& o, const Base& a, const Base& b)
{
    // TODO: Implement using intrinsics
    o.x = a.x + b.x;
    o.y = a.y + b.y;
    o.z = a.z + b.z;
}

template <typename T>
inline void
Vector3CalcCommon<T>::sub(Base& o, const Base& a, const Base& b)
{
    o.x = a.x - b.x;
    o.y = a.y - b.y;
    o.z = a.z - b.z;
}

template <>
inline void
Vector3CalcCommon<f32>::sub(Base& o, const Base& a, const Base& b)
{
    // TODO: Implement using intrinsics
    o.x = a.x - b.x;
    o.y = a.y - b.y;
    o.z = a.z - b.z;
}

// TODO
//template <typename T>
//inline void
//Vector3CalcCommon<T>::cross(Base& o, const Base& a, const Base& b)
//{
//}

template <>
inline void
Vector3CalcCommon<f32>::cross(Base& o, const Base& a, const Base& b)
{
    ASM_VECCrossProduct((const Vec*)&a, (const Vec*)&b, (Vec*)&o);
}

template <typename T>
inline T
Vector3CalcCommon<T>::dot(const Base& a, const Base& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <>
inline f32
Vector3CalcCommon<f32>::dot(const Base& a, const Base& b)
{
     // TODO: Implement using intrinsics
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T>
inline T
Vector3CalcCommon<T>::squaredLength(const Base& v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

template <typename T>
inline T
Vector3CalcCommon<T>::length(const Base& v)
{
    return MathCalcCommon<T>::sqrt(squaredLength(v));
}

template <>
inline f32
Vector3CalcCommon<f32>::length(const Base& v)
{
    return ASM_VECMag((const Vec*)&v);
}

template <typename T>
inline void
Vector3CalcCommon<T>::multScalar(Base& o, const Base& v, T t)
{
    o.x = v.x * t;
    o.y = v.y * t;
    o.z = v.z * t;
}

template <>
inline void
Vector3CalcCommon<f32>::multScalar(Base& o, const Base& v, f32 t)
{
    // TODO: Implement using intrinsics
    o.x = v.x * t;
    o.y = v.y * t;
    o.z = v.z * t;
}

template <typename T>
inline void
Vector3CalcCommon<T>::multScalarAdd(Base& o, T t, const Base& a, const Base& b)
{
    o.x = a.x * t + b.x;
    o.y = a.y * t + b.y;
    o.z = a.z * t + b.z;
}

template <>
inline void
Vector3CalcCommon<f32>::multScalarAdd(Base& o, f32 t, const Base& a, const Base& b)
{
    // TODO: Implement using intrinsics
    o.x = a.x * t + b.x;
    o.y = a.y * t + b.y;
    o.z = a.z * t + b.z;
}

template <typename T>
inline void
Vector3CalcCommon<T>::set(Base& o, const Base& v)
{
    o.x = v.x;
    o.y = v.y;
    o.z = v.z;
}

template <typename T>
inline void
Vector3CalcCommon<T>::set(Base& v, T x, T y, T z)
{
    v.x = x;
    v.y = y;
    v.z = z;
}

template <typename T>
inline void
Vector4CalcCommon<T>::set(Base& o, const Base& v)
{
    o.x = v.x;
    o.y = v.y;
    o.z = v.z;
    o.w = v.w;
}

template <typename T>
inline void
Vector4CalcCommon<T>::set(Base& v, T x, T y, T z, T w)
{
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
}

} // namespace sead
