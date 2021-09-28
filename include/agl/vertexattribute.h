#pragma once

#include <types.h>

namespace agl {

class VertexAttribute { // Size: 0xF4
public:
    VertexAttribute();
    virtual ~VertexAttribute();

    u8 _0[0xC][0x10];   // Array of 16 CLASS_2a26db8
    u32 _C0;
    u32 _C4;
    u8 _C8;
    u8 _C9;
    u8 _CA[34];         // Unknown values
    u32 _EC;
};

static_assert(sizeof(VertexAttribute) == 0xF4, "agl::VertexAttribute size mismatch");

}
