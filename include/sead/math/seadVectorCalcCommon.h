#ifndef SEAD_VECTORCALCCOMMON_H_
#define SEAD_VECTORCALCCOMMON_H_

#include "sead/math/seadMathPolicies.h"

namespace sead {

template <typename T>
class Vector2CalcCommon
{
public:
    typedef typename Policies<T>::Vec2Base Base;

public:
    static void add(Base& o, const Base& a, const Base& b);
    static void sub(Base& o, const Base& a, const Base& b);

    static void set(Base& o, const Base& v);
    static void set(Base& v, T x, T y);
};

template <typename T>
class Vector3CalcCommon
{
public:
    typedef typename Policies<T>::Vec3Base Base;

public:
    static void add(Base& o, const Base& a, const Base& b);
    static void sub(Base& o, const Base& a, const Base& b);

    static void cross(Base& o, const Base& a, const Base& b);
    static T dot(const Base& a, const Base& b);
    static T squaredLength(const Base& v);
    static T length(const Base& v);
    static void multScalar(Base& o, const Base& v, T t);
    static void multScalarAdd(Base& o, T t, const Base& a, const Base& b);
    static T normalize(Base& v);
    static void set(Base& o, const Base& v);
    static void set(Base& v, T x, T y, T z);
};

template <typename T>
class Vector4CalcCommon
{
public:
    typedef typename Policies<T>::Vec4Base Base;

public:
    static void set(Base& o, const Base& v);
    static void set(Base& v, T x, T y, T z, T w);
};

}  // namespace sead

#ifdef __cplusplus

#include "sead/math/seadVectorCalcCommon.hpp"

#endif // __cplusplus

#endif // SEAD_VECTORCALCCOMMON_H_
