#pragma once

#include <agl/texturedata.h>

namespace agl {

class RenderTargetDepth { // Size: 0x160
public:
    RenderTargetDepth();

    void initRegs_() const;
    void invalidateGPUCache() const;
    void onApplyTextureData_();

    // Begin inlined struct
    agl::TextureData base;
    u32 _9C;
    u32 viewMip;
    u32 viewFirstSlice;
    // End inlined struct
    u32 _A8;
    u32 _AC;
    u32 _B0;
    GX2DepthBuffer depthBuffer;
};

static_assert(sizeof(RenderTargetDepth) == 0x160, "agl::RenderTargetDepth size mismatch");

}

