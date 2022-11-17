#pragma once

#include "types.h"

namespace nw { namespace g3d {

class SkeletalAnimBlender {
public:
    SkeletalAnimBlender()
        : bufferPtr(nullptr)
    { }

    void ClearResult();

    size_t LCMount(void* lc, size_t size, bool load);
    void LCUnmount(bool store);

    void* resultBuffer;
    u16 maxBone;
    u16 numBone;
    mutable u32 flag;
    void* memResultBuffer;
    void* bufferPtr;
};

} }
