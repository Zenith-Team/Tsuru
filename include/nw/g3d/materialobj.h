#pragma once

#include "nw/g3d/res/resmaterial.h"
#include "nw/g3d/fnd/buffer.h"

namespace nw { namespace g3d {

namespace res { class ResTexture; }

class MaterialObj {
public:
    res::ResMaterial* res;
    u32 flag;
    u32* dirtyFlagArray;
    fnd::GfxBuffer matBlock;
    void* srcParam;
    res::ResTexture** textureArray;
    void* userPtr;
    void* bufferPtr;
    void* blockBuffer;
};

} }
