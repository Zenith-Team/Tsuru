#pragma once

#include <util/mtx.h>
#include <sead/runtimetypeinfo.h>

namespace sead {

class Camera {
    SEAD_RTTI_BASE(Camera)

public:
    Camera();
    virtual ~Camera();

    virtual void doUpdateMatrix(Mtx34* mtx) const = 0;

    Mtx34 matrix;
};

class LookAtCamera : public Camera {
    SEAD_RTTI_OVERRIDE(LookAtCamnera, Camera)

public:
    LookAtCamera(Vec3f& pos, Vec3f& at, Vec3f& up);
    virtual ~LookAtCamera();

    void doUpdateMatrix(Mtx34* mtx) const override;

    Vec3f pos;
    Vec3f at;
    Vec3f up;
};

}
