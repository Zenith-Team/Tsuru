#pragma once

#include "types.h"
#include "nw/agl/texture.h"
#include "dynamic_libs/gx2_types.h"

namespace agl{

class TextureData {
public:
    TextureData();

    void invalidateGPUCache();
    void initialize(TextureType, TextureFormat, u32 width, u32 height, u32 depth, u32 mipLevelNum, MultiSampleType);
    void loadGTX(void* data, u32);

    virtual void vf0C() deleted;

    TextureFormat format;
    GX2Surface surface;
    u32 width;
	u32 height;
	u32 depth;
	u32 size;
	u32 compSel1;
	u32 compSel2;
	u32 compSel3;
	u32 compSel4;
};


}
