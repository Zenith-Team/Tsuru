#pragma once

#include "math/seadVector.h"

class QuadraticBezier {
public:
    void set(const sead::Vector3f& kf0, const sead::Vector3f& kf1, const sead::Vector3f& kf2) {
        this->keyframes[0] = kf0;
        this->keyframes[1] = kf1;
        this->keyframes[2] = kf2;
    }

    void execute(sead::Vector3f* out, f32 t) {
        sead::Vector3f a, b;
        a.setLerp(this->keyframes[0], this->keyframes[1], t);
        b.setLerp(this->keyframes[1], this->keyframes[2], t);
        out->setLerp(a, b, t);
    }

    sead::Vector3f keyframes[3];
};
