#pragma once

#include "nw/eft/cafewrapper.h"

namespace nw { namespace eft {

class Primitive { // Size: 0x6C
public:
    Primitive() {
        this->initialized = false;
        this->numIndex = 0;
    }

    void Finalize(Heap* heap) {
        this->VBPos.Finalize(heap);
        this->VBNormal.Finalize(heap);
        this->VBColor.Finalize(heap);
        this->VBTexCoord.Finalize(heap);
        this->VBIndex.Finalize(heap);
    }

    bool initialized;
    u32 numIndex;
    VertexBuffer VBPos;
    VertexBuffer VBNormal;
    VertexBuffer VBColor;
    VertexBuffer VBTexCoord;
    VertexBuffer VBIndex;
    f32* pos;
    f32* normal;
    f32* color;
    f32* texCoord;
    u32* index;
};

static_assert(sizeof(Primitive) == 0x6C, "nw::eft::Primitive size mismatch");

} }
