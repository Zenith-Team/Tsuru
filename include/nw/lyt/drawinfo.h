#pragma once

#include "types.h"

namespace nw { namespace lyt {

class DrawInfo { // Size: 0xC8
public:
    u8 _0[0xC8]; // TODO: I'll do this later
};

} }

static_assert(sizeof(nw::lyt::DrawInfo) == 0xC8, "nw::lyt::DrawInfo size mismatch");
