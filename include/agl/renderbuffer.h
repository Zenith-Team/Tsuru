#pragma once

#include <sead/idisposer.h>
#include <sead/framebuffer.h>
#include <agl/rendertargetcolor.h>
#include <agl/rendertargetdepth.h>

namespace agl {

class RenderBuffer : public sead::IDisposer, public sead::FrameBuffer { // Size: 0x50
public:
    RenderBuffer();
    RenderBuffer(Vec2f& size, f32, f32, f32 sizeX, f32 sizeY);
    virtual ~RenderBuffer();

    SEAD_RTTI_OVERRIDE(RenderBuffer, sead::FrameBuffer)
    virtual void copyToDisplayBuffer(const sead::DisplayBuffer* displayBuffer);
    virtual void clear(u32, u32, const sead::Color4f& color, f32 depthValue, u32 stencilValue);
    virtual void bindImpl_();

    agl::RenderTargetColor* targetColors[8];
    agl::RenderTargetDepth* targetDepth;
};

static_assert(sizeof(RenderBuffer) == 0x50, "agl::RenderBuffer size mismatch");

}
