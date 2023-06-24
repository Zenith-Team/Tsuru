#pragma once

#include "types.h"
#include "agl/lyr/drawmethod.h"
#include "sead/viewport.h"
#include "sead/camera.h"
#include "sead/projection.h"

namespace agl { namespace lyr {

class Renderer;
class RenderStep;

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

    agl::lyr::Renderer* renderer;
    sead::Viewport viewport;
    sead::Viewport scissor;
    sead::Camera* camera;
    sead::Projection* projection;
    u32 _4C;
    u32 _50;
    u32 displayType;
    u32 renderDisplayFlag;
    s32 displayType2;
    sead::BitFlag32 flags;
    s32 index;
    u32 _68;
    sead::Color4f clearColor;
    f32 clearDepth;
    s32 renderStepCount;
    agl::lyr::RenderStep* renderSteps;
    u32 _88;
    DebugInfo debugInfo;
};

static_assert(sizeof(Layer) == 0x41C, "agl::lyr::Layer size mismatch");

} }
