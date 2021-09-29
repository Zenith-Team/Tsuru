#pragma once

#include <sead/idisposer.h>
#include <sead/framebuffer.h>
#include <agl/rendertargetcolor.h>
#include <agl/rendertargetdepth.h>

//! This header is highly inaccurate due to the equivalent inaccuracy of sead/framebuffer.h
//! Fix that first and then fix this

namespace agl {

class RenderBuffer : public sead::IDisposer { // Size: 0x50, //? Does this inherit sead::FrameBuffer?
public:
    RenderBuffer();
    RenderBuffer(Vec2f& size, f32, f32, f32 sizeX, f32 sizeY);
    virtual ~RenderBuffer();

    void clear(u32, u32 flags, sead::Color4f& color, f32 depthValue, u32 stencilValue) const;

    sead::FrameBuffer frameBuffer; //* Remove this if it *does* inherit sead::FrameBuffer
    u32 temp_padding;
    agl::RenderTargetColor* targetColors[8];
    agl::RenderTargetDepth* targetDepth;
};

static_assert(sizeof(RenderBuffer) == 0x50, "agl::RenderBuffer size mismatch");

}
