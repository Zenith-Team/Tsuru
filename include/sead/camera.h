#pragma once

#include "utils/mtx.h"
#include "sead/runtimetypeinfo.h"

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
    inline LookAtCamera()
        : Camera()
        , pos(0.0f, 0.0f, 10.0f)
        , at(0.0f, 0.0f, 0.0f)
        , up(0.0f, 1.0f, 0.0f)
    { }

    LookAtCamera(Vec3f& pos, Vec3f& at, Vec3f& up);

    virtual ~LookAtCamera();

    void doUpdateMatrix(Mtx34* mtx) const override;

    Vec3f pos;
    Vec3f at;
    Vec3f up;
};

class OrthoCamera : public LookAtCamera {
    SEAD_RTTI_OVERRIDE(OrthoCamera, LookAtCamera)

public:
    OrthoCamera();
    //virtual ~OrthoCamera();
};

}
