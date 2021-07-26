#pragma once

#include "types.h"
#include "sead/heap.h"

namespace sead {

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

    Heap* mParent;
    u32 mSize;
    u32 mCreateSlack;
    u32 mAdjustSlack;
    u8 mAdjust;
    u8 mTemporary;
    u8 mDontCreate;
};

class HeapPolicies {
public:
    HeapPolicy mPolicies[4];
    s32 mPrimaryIndex;
};

}
