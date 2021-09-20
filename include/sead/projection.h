#pragma once

#include <util/mtx.h>
#include <sead/runtimetypeinfo.h>

namespace sead {

class Graphics {
public:
    enum DevicePosture {
        DevicePosture_Same              = 0,
        DevicePosture_RotateRight       = 1,
        DevicePosture_RotateLeft        = 2,
        DevicePosture_RotateHalfAround  = 3,
        DevicePosture_FlipX             = 4,
        DevicePosture_FlipY             = 5,
        DevicePosture_FlipXY            = 3,
        DevicePosture_Invalid           = 4,
    };
};

class Projection { // Size: 0x94
    SEAD_RTTI_BASE(Projection)

public:
    Projection();
    Projection(f32, f32, f32, f32, f32, f32);
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

static_assert(sizeof(Projection) == 0x94, "sead::Projection size mismatch");

class OrthoProjection : public Projection { // Size: 0xAC
    SEAD_RTTI_OVERRIDE(OrthoProjection, Projection)

public:
    OrthoProjection();
    virtual ~OrthoProjection();

    u32 getProjectionType() const override;
    void doUpdateMatrix(Mtx44* mtx) const override;

    void doScreenPosToCameraPosTo(Vec3f*, const Vec3f&) const override; // deleted

    void setTBLR(f32 top, f32 bottom, f32 left, f32 right);

    f32 _94;
    f32 _98;
    f32 top;
    f32 bottom;
    f32 left;
    f32 right;
};

static_assert(sizeof(OrthoProjection) == 0xAC, "sead::OrthoProjection size mismatch");

}
