#pragma once

#include <types.h>

namespace nw { namespace eft {

class Heap;

class Config { // Size: 0x20
public:
    Config()
        : mHeap(NULL)
        , mNumEmitterMax(0x100)
        , mNumParticleMax(0x800)
        , mNumEmitterSetMax(0x80)
        , mNumResourceMax(1)
        , mNumStripeMax(0x100)
        , mDoubleBufferSize(0x20000)
    { }

    virtual ~Config() { }

    virtual void SetEffectHeap(Heap* heap) {
        this->mHeap = heap;
    }

    virtual Heap* GetEffectHeap() const {
        return this->mHeap;
    }

    Heap* mHeap;
    u32 mNumEmitterMax;
    u32 mNumParticleMax;
    u32 mNumEmitterSetMax;
    u32 mNumResourceMax;
    u32 mNumStripeMax;
    u32 mDoubleBufferSize;
};

static_assert(sizeof(Config) == 0x20, "Config size mismatch");

} }
