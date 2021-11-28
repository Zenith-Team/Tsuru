#pragma once

#include "sead/idisposer.h"
#include "agl/vertexbuffer.h"

namespace agl { namespace utl {

class PrimitiveVertex { // Size: 0x590
    SEAD_SINGLETON_DISPOSER(PrimitiveVertex)

public:
    PrimitiveVertex();
    virtual ~PrimitiveVertex();

    VertexBuffer vertexBuffers[3];
};

static_assert(sizeof(PrimitiveVertex) == 0x590, "agl::utl::PrimitiveVertex size mismatch");

} }
