#pragma once

#include "agl/lyr/layer.h"
#include "sead/projection.h"
#include "sead/camera.h"
#include "agl/lyr/displaytype.h"

namespace sead { class Viewport; class FrameBuffer; }
namespace agl { class DisplayList; }

namespace agl { namespace lyr {

class RenderInfo { // Size: 0x28
public:
    RenderInfo(DisplayType displayType, const sead::FrameBuffer* frameBuffer, bool, const Layer* parentLayer, DisplayList* displayList);

    s32 renderStepIndex;
    DisplayType displayType;
    sead::FrameBuffer* frameBuffer;
    s32 layerIndex; // Index in agl::lyr::Renderer layers buffer
    Layer* layer;
    sead::Camera* camera;
    sead::Projection* projection;
    sead::Viewport* viewport;
    DisplayList* displayList;
    bool _24;
};

static_assert(sizeof(RenderInfo) == 0x28, "agl::lyr::RenderInfo size mismatch");

} }
