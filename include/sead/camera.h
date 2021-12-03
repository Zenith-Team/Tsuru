#pragma once

#include <utils/mtx.h>
#include <sead/runtimetypeinfo.h>

namespace sead {

class Camera {
    SEAD_RTTI_BASE(Camera)

public:
    inline Camera() {
        this->matrix.makeIdentity();
    }

    virtual ~Camera();

    virtual void doUpdateMatrix(Mtx34* mtx) const = 0;

    Mtx34 matrix;
};

class LookAtCamera : public Camera {
    SEAD_RTTI_OVERRIDE(LookAtCamera, Camera)

public:
    inline LookAtCamera(sead::Vec3f& pos, sead::Vec3f& at, sead::Vec3f& up) {
        this->pos = pos;
        this->at = at;
        this->up = up;
    }

    virtual ~LookAtCamera();

    void doUpdateMatrix(Mtx34* mtx) const override;

    sead::Vec3f pos;
    sead::Vec3f at;
    sead::Vec3f up;
};

class OrthoCamera : public LookAtCamera {
    SEAD_RTTI_OVERRIDE(OrthoCamera, LookAtCamera)

public:
    OrthoCamera();
};

}
