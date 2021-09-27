#pragma once

#include <dynlibs/gx2/types.h>

namespace agl {

class TextureData { // Size: 0x9C
public:
    TextureData();

    virtual void vfC(); // deleted

    void initializeFromSurface(const GX2Surface& surface);
    void initializeSize_(u32, u32, u32);

    void invalidateGPUCache();

    void loadGTX(void* data, u32);

    void setMipLevelNum(u32 mip);

    u32 _0;
    GX2Surface surface;
    u32 width;
    u32 height;
    u32 depth;
    u32 size;
    u32 _88;
    u32 _8C;
    u32 _90;
    u32 _94;
};

static_assert(sizeof(TextureData) == 0x9C, "agl::TextureData size mismatch");

}
