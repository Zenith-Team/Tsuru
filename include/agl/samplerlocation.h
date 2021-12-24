#pragma once

#include "agl/shaderlocation.h"

namespace agl {

class SamplerLocation {
public:
    SamplerLocation()
        : location()
    { }

    sead::SafeString name;
    agl::ShaderLocation location;
};

static_assert(sizeof(SamplerLocation) == 0x10, "agl::SamplerLocation size mismatch");

}
