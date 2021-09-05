#pragma once

#include <util/mtx.h>
#include <sead/runtimetypeinfo.h>

namespace sead {

class Graphics {
public:
    enum DevicePosture {
        cDevicePosture_Same = 0,
        cDevicePosture_RotateRight = 1,
        cDevicePosture_RotateLeft = 2,
        cDevicePosture_RotateHalfAround = 3,
        cDevicePosture_FlipX = 4,
        cDevicePosture_FlipY = 5,
        cDevicePosture_FlipXY = 3,
        cDevicePosture_Invalid = 4,
    };
};

class Projection {
    SEAD_RTTI_BASE(Projection)

public:
    Projection();
    virtual ~Projection();

    virtual u32 getProjectionType() const = 0;
    virtual void doUpdateMatrix(Mtx44* mtx) const = 0;
    virtual void doUpdateDeviceMatrix(Mtx44*, const Mtx44&, Graphics::DevicePosture) const;
    virtual void doScreenPosToCameraPosTo(Vec3f*, const Vec3f&) const = 0;

    void updateMatrixImpl_() const;
    const Mtx44& getDeviceProjectionMatrix() const;

    mutable bool dirty;
    mutable bool deviceDirty;
    Mtx44 matrix;
    Mtx44 deviceMatrix;
    Graphics::DevicePosture devicePosture;
    f32 deviceZScale;
    f32 deviceZOffset;
};

}
