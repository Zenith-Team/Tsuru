#pragma once

#include <types.h>
#include <nw/eft/emitterset.h>

namespace nw { namespace eft {

class Handle {
public:
    Handle()
        : emitterSet(NULL)
    { }

    EmitterSet* emitterSet;
    u32 createID;
};

} }
