#pragma once

#include "dynlibs/os/functions.h"

#include "sead/math/seadMathCalcCommon.h"

namespace sead {

template <>
inline void
Matrix34CalcCommon<f32>::makeIdentity(Base& o)
{
    ASM_MTXIdentity(o.m);
}

template <>
inline void
Matrix34CalcCommon<f32>::copy(Base& o, const Base& n)
{
    ASM_MTXCopy(const_cast<f32(*)[4]>(n.m), o.m);
}

// Nintendo did not actually use this for the cafe f32 specialization

template <>
inline void
Matrix34CalcCommon<f32>::copy(Base& o, const Mtx44& n)
{
    ASM_MTXCopy(const_cast<f32(*)[4]>(n.m), o.m);
}

template <>
inline void
Matrix34CalcCommon<f32>::inverse(Base& o, const Base& n)
{
    u32 ret = ASM_MTXInverse(const_cast<f32(*)[4]>(n.m), o.m);

    // Nintendo did not actually call makeIdentity() for the cafe f32 specialization
    if (!ret)
        return makeIdentity(o);
}

template <>
inline void
Matrix34CalcCommon<f32>::multiply(Base& o, const Base& a, const Base& b)
{
    ASM_MTXConcat(const_cast<f32(*)[4]>(a.m), const_cast<f32(*)[4]>(b.m), o.m);
}

// Nintendo did not actually use this for the cafe f32 specialization

template <>
inline void
Matrix34CalcCommon<f32>::transposeTo(Base& o, const Base& n)
{
    ASM_MTXTranspose(const_cast<f32(*)[4]>(n.m), o.m);
}

template <>
inline void
Matrix34CalcCommon<f32>::makeS(Base& o, const Vec3& s)
{
    ASM_MTXScale(o.m, s.x, s.y, s.z);
}

template <>
inline void
Matrix44CalcCommon<f32>::makeIdentity(Base& o)
{
    ASM_MTX44Identity(o.m);
}

template <>
inline void
Matrix44CalcCommon<f32>::copy(Base& o, const Base& n)
{
    ASM_MTX44Copy(const_cast<f32(*)[4]>(n.m), o.m);
}

// Nintendo did not actually use this for the cafe f32 specialization

template <>
inline void
Matrix44CalcCommon<f32>::copy(Base& o, const Mtx34& n, const Vec4& v)
{
    ASM_MTXCopy(const_cast<f32(*)[4]>(n.m), o.m);

    o.m[3][0] = v.x;
    o.m[3][1] = v.y;
    o.m[3][2] = v.z;
    o.m[3][3] = v.w;
}

template <>
inline void
Matrix44CalcCommon<f32>::multiply(Base& o, const Base& a, const Base& b)
{
    ASM_MTX44Concat(const_cast<f32(*)[4]>(a.m), const_cast<f32(*)[4]>(b.m), o.m);
}

} // namespace sead
