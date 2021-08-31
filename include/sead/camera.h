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

    Mtx34 mMatrix;
};

}
