#pragma once

#include "sead.h"
#include "nw/agl/render/rendertargetcolor.h"
#include "nw/agl/render/rendertargetdepth.h"

namespace agl { class RenderBuffer : public sead::IDisposer {
public:
    RenderBuffer();
    RenderBuffer(Vec2* size, f32, f32, f32, f32);
    virtual ~RenderBuffer();

    void clear(u32, u32 flags, sead::Color4f* color, u32 stencilValue, f32 depthValue);

    sead::FrameBuffer frameBuffer;
    RenderTargetColor* targetColors[8];
    RenderTargetDepth* targetDepth;
};

}