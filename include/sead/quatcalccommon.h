#pragma once

#include "sead/quat.h"
#include "sead/mathcalccommon.h"

namespace sead {

template <typename T>
class QuatCalcCommon
{
public:
    static void makeUnit(Quat<T>& q)
    {
        set(q, 0.0f, 0.0f, 0.0f, 1.0f);
    }

    static bool makeVectorRotation(Quat<T>& q, const Vector3<T>& from, const Vector3<T>& to)
    {
        Vector3<T> cross;
        cross = from.crossedWith(to);
        const T dot = from.dot(to) + 1;

        if (dot <= MathCalcCommon<T>::epsilon())
        {
            makeUnit(q);
            return false;
        }
        else
        {
            T v1 = MathCalcCommon<T>::sqrt(2 * dot);
            T v2 = 1 / v1;
            set(q, v1 * 0.5f,
                cross.x * v2, cross.y * v2, cross.z * v2);
        }

        return true;
    }

    static void set(Quat<T>& q, T w, T x, T y, T z)
    {
        q.w = w;
        q.x = x;
        q.y = y;
        q.z = z;
    }

};

}
