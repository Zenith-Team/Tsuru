#pragma once

#include "types.h"

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
    u32 renderStepIdx;
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
