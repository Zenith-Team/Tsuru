#pragma once

#include <types.h>

namespace sead {

class Camera;
class Projection;
class Viewport;

}

namespace agl {

class DisplayList;
class RenderBuffer;

namespace lyr {

class Layer;

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

}

}
