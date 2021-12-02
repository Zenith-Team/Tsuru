#ifndef SEAD_PROJECTION_H_
#define SEAD_PROJECTION_H_

#include "gfx/seadGraphics.h"
#include "sead/math/seadMatrix.h"
#include "sead/math/seadVector.h"
#include "sead/prim/seadRuntimeTypeInfo.h"

namespace sead {

class Projection
{
    SEAD_RTTI_BASE(Projection)

public:
    Projection();
    virtual ~Projection();

    virtual u32 getProjectionType() const = 0;
    virtual void doUpdateMatrix(Matrix44f* mtx) const = 0;
    virtual void doUpdateDeviceMatrix(Matrix44f*, const Matrix44f&, Graphics::DevicePosture) const;
    virtual void doScreenPosToCameraPosTo(Vector3f*, const Vector3f&) const = 0;

    void updateMatrixImpl_() const;
    const Matrix44f& getDeviceProjectionMatrix() const;

    mutable bool mDirty;
    mutable bool mDeviceDirty;
    Matrix44f mMatrix;
    Matrix44f mDeviceMatrix;
    Graphics::DevicePosture mDevicePosture;
    f32 mDeviceZScale;
    f32 mDeviceZOffset;
};

} // namespace sead

#endif // SEAD_PROJECTION_H_
