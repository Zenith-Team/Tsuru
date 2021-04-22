#pragma once

#include "types.h"

namespace sead {

class Heap;

class HeapArray {
public:
    HeapArray(HeapArray& other);

    Heap* mHeaps[4];
    bool mAdjusted[4];
    s32 mPrimaryIndex;
};

class HeapPolicy {
public:
    HeapPolicy();

    Heap* parent;
    u32 size;
    u32 create_slack;
    u32 adjust_slack;
    u8 adjust;
    u8 temporary;
    u8 dont_create;
};

class HeapPolicies {
public:
    HeapPolicy mPolicies[4];
    s32 mPrimaryIndex;
};

}
