#pragma once

#include "sead/safestring.h"

namespace agl {

class ShaderLocation {
public:
    ShaderLocation()
        : vs(-1)
        , ps(-1)
        , gs(-1)
    { }

    s16 vs;
    s16 ps;
    s16 gs;
};

static_assert(sizeof(ShaderLocation) == 0x6, "agl::ShaderLocation size mismatch");

}
