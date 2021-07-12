#ifndef EFT_PRIMITIVE_H_
#define EFT_PRIMITIVE_H_

#include "nw/eft/cafewrapper.h"

namespace nw { namespace eft {

class Primitive {
public:
    Primitive() {
        initialized = false;
        numIndex = 0;
    }

    // convenience
    void Finalize(Heap* heap) {
        vbPos.Finalize(heap);
        vbNormal.Finalize(heap);
        vbColor.Finalize(heap);
        vbTexCoord.Finalize(heap);
        vbIndex.Finalize(heap);
    }

    bool initialized;
    u32 numIndex;
    VertexBuffer vbPos;
    VertexBuffer vbNormal;
    VertexBuffer vbColor;
    VertexBuffer vbTexCoord;
    VertexBuffer vbIndex;
    f32* pos;
    f32* normal;
    f32* color;
    f32* texCoord;
    u32* index;
};
static_assert(sizeof(Primitive) == 0x6C, "Primitive size mismatch");

} } // namespace nw::eft

#endif // EFT_PRIMITIVE_H_
