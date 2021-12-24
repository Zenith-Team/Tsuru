#pragma once

#include "dynlibs/gx2/types.h"

namespace agl {

enum TextureFormat { };
enum TextureCompSel { };

class TextureData { // Size: 0x9C
public:
    TextureData();

    virtual void vfC(); // deleted

    void initialize_(u32 textureType, u32 textureFormat, u32 width, u32 height, u32 depth, bool mipLevelNum, u32 multiSampleType);
    void initializeSize_(u32, u32, u32);
    void initializeFromSurface(const GX2Surface& surface);

    void invalidateGPUCache();

    void setMipLevelNum(u32 mip);

    TextureFormat format;
    GX2Surface surface;
    u32 width;
    u32 height;
    u32 depth;
    u32 size;
    TextureCompSel compSel[4];
};

static_assert(sizeof(TextureData) == 0x9C, "agl::TextureData size mismatch");

}
