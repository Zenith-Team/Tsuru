#pragma once

#include "sead/heap.h"

class Mask { // Size: 0x4
public:
    ENUM_CLASS(Shape,
        Cave,
        CaveSmall,
        Dark,
        DeepSea,
        FlashlightA,
        FlashlightB,
        DRCBlock,
        DRCTouch
    );

public:
    virtual bool init(sead::Heap* heap, u32 shape) = 0;
    virtual bool update() = 0;
    virtual bool draw() = 0;
};

static_assert(sizeof(Mask) == 0x4, "Mask size mismatch");
