#pragma once

#include <types.h>

namespace nw { namespace snd {

class SoundMemoryAllocatable
{
public:
    virtual ~SoundMemoryAllocatable()
    {
    }

    virtual void* Alloc(size_t size) = 0;
};

} }
