#pragma once

#include "dynlibs/gx2/types.h"

namespace nw { namespace g3d { namespace fnd {

struct GfxBuffer_t {
    union {
        void* data;
        u32 dataUIntPtr;
    };
    u32 size;
    u32 handle;
    u16 stride;
    u16 numBuffering;
    union {
        void* contextPtr; // GX2StreamOutContext*
        u32 contextUIntPtr;
    };
};

class GfxBuffer : public GfxBuffer_t {
    // TODO
};

} } }
