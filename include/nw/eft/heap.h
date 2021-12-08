#pragma once

#include "types.h"

namespace nw { namespace eft {

class Heap {
public:
    Heap() { }
    virtual ~Heap() { }

    virtual void* Alloc(u32 size, s32 alignment = 0x80) = 0;
    virtual void Free(void* ptr) = 0;
};

static_assert(sizeof(Heap) == 4, "nw::eft::Heap size mismatch");

} }
