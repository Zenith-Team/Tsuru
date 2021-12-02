#pragma once

#include "sead/idisposer.h"

namespace agl { namespace utl {

class DebugTexturePage : public sead::IDisposer { // Size: 0x1DC
public:
    u8 _0[0x1DC - 0x10];   // TODO: I'll do this later
};

static_assert(sizeof(DebugTexturePage) == 0x1DC, "agl::utl::DebugTexturePage size mismatch");

} }
