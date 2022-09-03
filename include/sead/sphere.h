#pragma once

#include "sead/vector.h"

namespace sead {

template <typename VectorType>
class Sphere {
private:
    typedef VectorType::ValueType T;

public:
    Sphere()
        : center()
        , radius(0)
    { }

    Sphere(const VectorType& center, T radius)
        : center(center)
        , radius(radius)
    { }

    VectorType center;
    T radius;
};

typedef Sphere<Vector2<f32> > Sphere2f;
typedef Sphere<Vector3<f32> > Sphere3f;

}
