#pragma once

#include <sead/heap.h>

class Mask { // Size: 0x4
public:
    virtual bool init(sead::Heap* heap, u32 type) = 0;
    virtual bool update() = 0;
    virtual bool draw() = 0;
};

static_assert(sizeof(Mask) == 0x4, "Mask size mismatch");
