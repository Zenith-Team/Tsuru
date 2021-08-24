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
    u32 mRenderStepIndex;
    u32 mDisplayType;
    RenderBuffer* mFrameBuffer;
    u32 _C;
    Layer* mParentLayer;
    sead::Camera* mCamera;
    sead::Projection* mProjection;
    sead::Viewport* mViewport;
    DisplayList* mDisplayList;
    bool _24;
};

} }
