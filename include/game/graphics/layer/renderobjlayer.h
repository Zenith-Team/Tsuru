#pragma once

#include "nw/g3d.h"
#include "game/graphics/layer/objlayer.h"

class SkeletalAnimation;
class TextureAnimation;
class ShaderAnimation;
class VisibilityAnimation;
class ShapeAnimation;

class RenderObjLayer : public ObjLayer {
public:
    RenderObjLayer();
    virtual ~RenderObjLayer();

    u32 getRenderStepNum() const override;
    void getRenderStepName(sead::SafeString* name, s32 idx) const override;
    void doInitialize(sead::Heap* heap) override;

    u32 vf54() override;

    void vf64(s32) override;

    Mtx44 _42C;
    u8 _46C;
    f32 _470;
    f32 _474;
};

static_assert(sizeof(RenderObjLayer) == 0x478, "RenderObjLayer size mismatch");
