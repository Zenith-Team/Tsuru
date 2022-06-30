#pragma once

#include "types.h"
#include "agl/lyr/drawmethod.h"
#include "sead/viewport.h"
#include "sead/camera.h"
#include "sead/projection.h"

namespace agl { namespace lyr {

class Layer : public sead::IDisposer { // Size: 0x41C
private:
    struct DebugInfo {
        u8 _0[0x390]; // TODO: I'll do this later
    };

public:
    Layer();
    virtual ~Layer();

    SEAD_RTTI_BASE(Layer);
    virtual u32 getRenderStepNum() const = 0;
    virtual void getRenderStepName(sead::SafeString* name, s32 idx) const = 0;
    virtual void doInitialize(sead::Heap* heap);
    virtual void vf3C();
    virtual void preDrawImpl(const RenderInfo& renderInfo) const; // Called before draw
    virtual void postDrawImpl(const RenderInfo& renderInfo) const; // Called after draw
    virtual u32 vf54();
    virtual u32 vf5C();

    void initialize_(sead::Heap* heap);

    DrawMethodImplBase* pushBackDrawMethod(u32 renderStepIdx, DrawMethodImplBase* drawMethod);
    DrawMethodImplBase* pushBackDrawMethod(DrawMethodImplBase* drawMethod);

    u8 _10[0x4];
    sead::Viewport _14;
    sead::Viewport scissor;
    sead::Camera* camera;
    sead::Projection* projection;
    u32 _4C;
    u32 _50;
    u32 _54;
    u8 _58[0x4];
    s32 _5C;
    u32 _60;
    u32 _64;
    u32 _68;
    f32 _6C;
    f32 _70;
    f32 _74;
    f32 _78;
    f32 _7C;
    Vec2i _80;
    u32 _88;
    DebugInfo debugInfo;
};

static_assert(sizeof(Layer) == 0x41C, "agl::lyr::Layer size mismatch");

} }
