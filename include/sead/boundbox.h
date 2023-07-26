#pragma once

#include "types.h"
#include "sead/vector.h"

namespace sead {

template <typename T>
struct BoundBox2 {
    BoundBox2(T t)
        : min(t)
        , max(t)
    { }

    BoundBox2(const Vector2<T>& minV, const Vector2<T>& maxV)
        : min(minV)
        , max(maxV)
    { }

    T getSizeX() const
    {
        return max.x - min.x;
    }

    T getSizeY() const
    {
        return max.y - min.y;
    }

    Vector2<T> getCenter() const
    {
        return Vector2((min.x + max.x) / 2.0f, (min.y + max.y) / 2.0f);
    }

    void getCenter(Vector2<T>* center) const
    {
        center->set((min.x + max.x) / 2.0f, (min.y + max.y) / 2.0f);
    }

    sead::Vector2<T> min;
    sead::Vector2<T> max;

    static const BoundBox2<T> sUndefined;
};

template <typename T>
struct BoundBox3 {
    BoundBox3(const Vector3<T>& minV, const Vector3<T>& maxV)
        : min(minV)
        , max(maxV)
    { }

    sead::Vector3<T> min;
    sead::Vector3<T> max;

    static const BoundBox3<T> sUndefined;
};

typedef BoundBox2<f32> BoundBox2f;
typedef BoundBox3<f32> BoundBox3f;

}
