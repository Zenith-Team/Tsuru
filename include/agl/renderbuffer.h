#pragma once

#include "sead/idisposer.h"
#include "sead/framebuffer.h"
#include "agl/rendertarget.h"

namespace agl {

class RenderBuffer : public sead::IDisposer, public sead::FrameBuffer { // Size: 0x50
public:
    RenderBuffer();
    RenderBuffer(const Vec2f& virtualSsize, f32 physicalX, f32 physicalY, f32 physicalW, f32 physicalH);
    virtual ~RenderBuffer();

    SEAD_RTTI_OVERRIDE(RenderBuffer, sead::FrameBuffer);
    virtual void copyToDisplayBuffer(const sead::DisplayBuffer* displayBuffer) const;
    virtual void clear(u32 clearFlag, const sead::Color4f& color, f32 depth, u32 stencil) const;
    virtual void bindImpl_() const;

    void initialize();
    void setRenderTargetColorNullAll();

    RenderTarget<RenderTargetColor>* targetColors[8];
    RenderTarget<RenderTargetDepth>* targetDepth;
};

static_assert(sizeof(RenderBuffer) == 0x50, "agl::RenderBuffer size mismatch");

}
