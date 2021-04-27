#pragma once

#include "dynamic_libs/gx2_types.h"
#include "nw/agl/texture/texturedata.h"

namespace agl { class RenderTargetColor {
public:
    RenderTargetColor();

    void invalidateGPUCache();
    void applyTextureData(agl::TextureData*);

    TextureData textureData;
    u32 _9C;
    u32 vieMip;
    u32 viewFirstSlice;
    u8 _A8;
    u8 _A9;
    u8 _AA;
    u8 _AB;
    u32 auxBufferSize;
    u32 auxBufferAlign;
    u32 _B4;
    GX2ColorBuffer colorBuffer;
};

}
