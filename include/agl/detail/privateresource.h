#pragma once

#include "sead/idisposer.h"
#include "sead/heap.h"

namespace agl { namespace detail {

class PrivateResource { // Size: 0x70
    SEAD_SINGLETON_DISPOSER(PrivateResource)

public:
    PrivateResource();
    virtual ~PrivateResource();

    void initialize(sead::Heap* workHeapParent, sead::Heap* shaderCompileHeapParent, u32 workHeapSize, u32 shaderCompileHeapSize);

    sead::ExpHeap* workHeap;
    sead::ExpHeap* shaderCompileHeap;
    u32 _18;
    Vec2u _1C;
    u32 _24;
    u8 _28[4]; // Unknown values
    sead::Heap* shaderCompileHeapParent;
    sead::CriticalSection criticalSection;
};

static_assert(sizeof(PrivateResource) == 0x70, "agl::PrivateResource size mismatch");

} }
