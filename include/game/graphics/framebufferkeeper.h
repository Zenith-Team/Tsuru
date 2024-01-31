#pragma once

#include "heap/seadDisposer.h"
#include "sead/graphicscontext.h"
#include "agl/utl/debugtexturepage.h"
#include "agl/texturedata.h"
#include "agl/rendertargetcolor.h"

struct FrameBufferCapture {
    agl::TextureData* textureData;
    agl::TextureFormat format;
    u32 width;
    u32 height;
    u8 _10[4];
    agl::RenderTargetColor* colorTarget;
    u8 _18[0x28 - 0x18];
    void* resTexture;
    u32 refCount;
    u8 _30[4];
    u32 allocateType;
};

static_assert(sizeof(FrameBufferCapture) == 0x38, "FrameBufferCapture size mismatch");

class FrameBufferKeeper {
    SEAD_SINGLETON_DISPOSER(FrameBufferKeeper);

public:
    FrameBufferKeeper();

    FrameBufferCapture buffers[5];
    sead::GraphicsContext context;
    agl::utl::DebugTexturePage debugTexturePage;
};

static_assert(sizeof(FrameBufferKeeper) == 0x378, "FrameBufferKeeper size mismatch");
