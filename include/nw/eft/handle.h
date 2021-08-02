#pragma once

#include "types.h"
#include "nw/eft/emitterset.h"

namespace nw { namespace eft {

class Handle {
public:
    Handle()
        : mEmitterSet(NULL)
    { }

    EmitterSet* mEmitterSet;
    u32 mCreateID;
};

static_assert(sizeof(Handle) == 8, "Handle size mismatch");

} }
