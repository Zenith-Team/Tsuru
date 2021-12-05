#pragma once

#include "types.h"

namespace nw { namespace eft {

class Heap;

class Config { // Size: 0x20
public:
    Config()
        : heap(NULL)
        , numEmitterMax(0x100)
        , numParticleMax(0x800)
        , numEmitterSetMax(0x80)
        , numResourceMax(1)
        , numStripeMax(0x100)
        , doubleBufferSize(0x20000)
    { }

    virtual ~Config() { }

    virtual void SetEffectHeap(Heap* heap) {
        this->heap = heap;
    }

    virtual Heap* GetEffectHeap() const {
        return this->heap;
    }

    Heap* heap;
    u32 numEmitterMax;
    u32 numParticleMax;
    u32 numEmitterSetMax;
    u32 numResourceMax;
    u32 numStripeMax;
    u32 doubleBufferSize;
};

static_assert(sizeof(Config) == 0x20, "nw::eft::Config size mismatch");

} }
