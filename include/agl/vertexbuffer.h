#pragma once

#include <types.h>

namespace agl {

class VertexBuffer { // Size: 0x1D4
public:
    VertexBuffer();
    virtual ~VertexBuffer();

    u8 _0[0x1C][0x10];  // Array of 16 CLASS_2a270fc
    u32 _1C0;
    u32 _1C4;
    u32 _1C8;
    u32 _1CC;
};

static_assert(sizeof(VertexBuffer) == 0x1D4, "agl::VertexBuffer size mismatch");

}
