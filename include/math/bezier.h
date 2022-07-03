#pragma once

#include "sead/vector.h"

class QuadraticBezier {
public:
    void set(const Vec3f& kf0, const Vec3f& kf1, const Vec3f& kf2) {
        this->keyframes[0] = kf0;
        this->keyframes[1] = kf1;
        this->keyframes[2] = kf2;
    }

    void execute(Vec3f* out, f32 t) {
        Vec3f a = this->keyframes[0]; a.lerp(this->keyframes[1], t);
        Vec3f b = this->keyframes[1]; b.lerp(this->keyframes[2], t);
        Vec3f pos = a; pos.lerp(b, t);

        *out = pos;
    }

    Vec3f keyframes[3];
};
