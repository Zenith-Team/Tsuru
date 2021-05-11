#pragma once

#include "sead/runtimetypeinfo.h"
#include "util/mtx34.h"

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
