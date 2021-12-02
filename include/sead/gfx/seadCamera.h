#ifndef SEAD_CAMERA_H_
#define SEAD_CAMERA_H_

#include "sead/math/seadMatrix.h"
#include "sead/prim/seadRuntimeTypeInfo.h"

namespace sead {

class Camera
{
    SEAD_RTTI_BASE(Camera)

public:
    Camera();
    virtual ~Camera();

    virtual void doUpdateMatrix(Matrix34f* mtx) const = 0;

    Matrix34f mMatrix;
};

} // namespace sead

#endif // SEAD_CAMERA_H_
