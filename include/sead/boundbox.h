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

    sead::Vector2<T> min;
    sead::Vector2<T> max;

    static const BoundBox2<T> sUndefined;
};

template <typename T>
struct BoundBox3 {
    sead::Vector3<T> min;
    sead::Vector3<T> max;

    static const BoundBox3<T> sUndefined;
};

typedef BoundBox2<f32> BoundBox2f;
typedef BoundBox3<f32> BoundBox3f;

}
