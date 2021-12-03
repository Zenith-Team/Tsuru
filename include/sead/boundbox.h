#pragma once

#include <types.h>

namespace sead {

template <typename T>
struct BoundBox2 {
    BoundBox2(T t)
        : min(t)
        , max(t)
    { }

    Vector2<T> min;
    Vector2<T> max;

    static const BoundBox2<T> sUndefined;
};

template <typename T>
struct BoundBox3 {
    Vector3<T> min;
    Vector3<T> max;

    static const BoundBox3<T> sUndefined;
};

}
