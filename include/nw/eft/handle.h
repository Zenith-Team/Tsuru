#pragma once

#include "types.h"
#include "nw/eft/emitterset.h"

namespace nw { namespace eft {

class Handle {
public:
    Handle()
        : emitterSet(NULL)
    { }

    EmitterSet* emitterSet;
    u32 createID;
};

static_assert(sizeof(Handle) == 8, "nw::eft::Handle size mismatch");

} }
