#pragma once

#include "agl/texturesampler.h"
#include "sead/idisposer.h"

namespace agl { namespace utl {

class PrimitiveTexture { // 0x11F4
    SEAD_SINGLETON_DISPOSER(PrimitiveTexture)

public:
    PrimitiveTexture();
    virtual ~PrimitiveTexture();

    TextureSampler samplers[11];
};

static_assert(sizeof(PrimitiveTexture) == 0x11F4, "agl::utl::PrimitiveTexture size mismatch");

} }
