#pragma once

#include "sead/heap.h"

class Mask { // Size: 0x4
public:
    enum MaskShape {
        MaskShape_Cave,
        MaskShape_CaveSmall,
        MaskShape_Dark,
        MaskShape_DeepSea,
        MaskShape_FlashlightA,
        MaskShape_FlashlightB,
        MaskShape_DRCBlock,
        MaskShape_DRCTouch
    };

public:
    virtual bool init(sead::Heap* heap, u32 shape) = 0;
    virtual bool update() = 0;
    virtual bool draw() = 0;
};

static_assert(sizeof(Mask) == 0x4, "Mask size mismatch");
