#pragma once

#include "sead/math/seadQuat.h"

namespace sead {

template <typename T>
inline void
QuatCalcCommon<T>::makeUnit(Base& q)
{
    q = Quat<T>::unit;
}

template <typename T>
inline void
QuatCalcCommon<T>::set(Base& q, T w, T x, T y, T z)
{
    q.w = w;
    q.x = x;
    q.y = y;
    q.z = z;
}

} // namespace sead
