#pragma once

#include "sead/mathpolicies.h"
#include "sead/vector.h"

namespace sead {

template <typename T>
class Quat : public Policies<T>::QuatBase {
private:
    typedef Quat<T> Self;
    typedef Vector3<T> Vec3;

public:
    Quat() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->w = 0;
    }

    Quat(T w_, T x_, T y_, T z_);

    void makeUnit();
    bool makeVectorRotation(const Vec3& from, const Vec3& to);
    void set(T w_, T x_, T y_, T z_);

    static const Quat unit;
};

typedef Quat<f32> Quatf;

static_assert(sizeof(Quatf) == 0x10, "sead::Quat<T> size mismatch");

template <>
extern const Quat<f32> Quat<f32>::unit;

}

#include "sead/quatcalccommon.h"

namespace sead {

template <typename T> inline Quat<T>::Quat(T w_, T x_, T y_, T z_) { QuatCalcCommon<T>::set(*this, w_, x_, y_, z_); }
template <typename T> inline bool Quat<T>::makeVectorRotation(const Vec3& from, const Vec3& to) { return QuatCalcCommon<T>::makeVectorRotation(*this, from, to); }

}
