#pragma once

#include <types.h>

namespace sead {

template <typename T>
struct BoundBox2 {
    BoundBox2(T t)
        : min(t)
        , max(t)
    { }

    Vec2<T> min;
    Vec2<T> max;

    static const BoundBox2<T> sUndefined;
};

template <typename T>
struct BoundBox3 {
    Vec3<T> min;
    Vec3<T> max;

    static const BoundBox3<T> sUndefined;
};

}
