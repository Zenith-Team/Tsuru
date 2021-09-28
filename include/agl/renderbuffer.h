#pragma once

#include <sead/idisposer.h>
#include <sead/framebuffer.h>
#include <agl/rendertargetcolor.h>
#include <agl/rendertargetdepth.h>

//! This header is highly inaccurate due to the equivalent inaccuracy of sead/framebuffer.h
//! Fix that first and then fix this

namespace agl {

class RenderBuffer { // Size: 0x50, inherits sead::IDisposer and possibly also sead::FrameBuffer
public:
    RenderBuffer();
    RenderBuffer(Vec2f& size, f32, f32, f32 sizeX, f32 sizeY);
    virtual ~RenderBuffer();

    u8 _0[0x10];
    sead::FrameBuffer frameBuffer;
    u8 _28[0x4C - 0x28];
};

static_assert(sizeof(RenderBuffer) == 0x50, "agl::RenderBuffer size mismatch");

}
