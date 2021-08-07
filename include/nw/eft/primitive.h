#pragma once

#include <nw/eft/cafewrapper.h>

namespace nw { namespace eft {

class Primitive { // Size: 0x6C
public:
    Primitive() {
        this->mInitialized = false;
        this->mNumIndex = 0;
    }

    void Finalize(Heap* heap) {
        this->mVBPos.Finalize(heap);
        this->mVBNormal.Finalize(heap);
        this->mVBColor.Finalize(heap);
        this->mVBTexCoord.Finalize(heap);
        this->mVBIndex.Finalize(heap);
    }

    bool mInitialized;
    u32 mNumIndex;
    VertexBuffer mVBPos;
    VertexBuffer mVBNormal;
    VertexBuffer mVBColor;
    VertexBuffer mVBTexCoord;
    VertexBuffer mVBIndex;
    f32* mPos;
    f32* mNormal;
    f32* mColor;
    f32* mTexCoord;
    u32* mIndex;
};

static_assert(sizeof(Primitive) == 0x6C, "Primitive size mismatch");

} }
