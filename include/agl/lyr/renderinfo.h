#pragma once

#include <types.h>
#include <agl/lyr/layer.h>
#include <sead/projection.h>
#include <sead/camera.h>

namespace sead { class Viewport; }
namespace agl { class DisplayList; class RenderBuffer; }

namespace agl { namespace lyr {

class RenderInfo {
public:
    u32 renderStepIndex;
    u32 displayType;
    RenderBuffer* frameBuffer;
    u32 _C;
    Layer* parentLayer;
    sead::Camera* camera;
    sead::Projection* projection;
    sead::Viewport* viewport;
    DisplayList* displayList;
    bool _24;
};

} }
