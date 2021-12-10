#pragma once

#include "sead/safestring.h"

namespace agl {

class SamplerLocation {
public:
    SamplerLocation()
    { }

    sead::SafeString name;
    
    // agl::ShaderLocation
    s16 vsLoc;
    s16 psLoc;
    s16 gsLoc;
};

static_assert(sizeof(SamplerLocation) == 0x10, "agl::SamplerLocation size mismatch");

}
