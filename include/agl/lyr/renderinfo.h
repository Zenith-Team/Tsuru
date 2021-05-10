#pragma once

#include "sead.h"
#include "agl/lyr/display.h"
#include "agl/lyr/layer.h"

namespace agl { namespace lyr { class RenderInfo {
public:
    s32 step;
    DisplayType displayType;
    sead::FrameBuffer* frameBuffer;
    u32 _C;
    Layer* layer;
    void* _14;
    sead::Projection* projection;
    sead::Viewport* viewport;
    DisplayList* displaylist;
    u32 _24;
};

}}
