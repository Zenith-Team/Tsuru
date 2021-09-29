#pragma once

#include <types.h>
#include <agl/lyr/layer.h>
#include <sead/projection.h>
#include <sead/camera.h>

namespace sead { class Viewport; class FrameBuffer; }
namespace agl { class DisplayList; class RenderBuffer; }

namespace agl { namespace lyr {

class RenderInfo { // Size: 0x28
public:
    // TODO: Two constructors here

    u32 renderStepIndex;
    u32 displayType;
    RenderBuffer* renderBuffer;
    u32 _C;
    Layer* layer;
    sead::Camera* camera;
    sead::Projection* projection;
    sead::Viewport* viewport;
    DisplayList* displayList;
    bool _24;
};

static_assert(sizeof(RenderInfo) == 0x28, "agl::lyr::RenderInfo size mismatch");

} }
