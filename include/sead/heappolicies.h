#pragma once

#include <types.h>
#include <sead/heap.h>

namespace sead {

class HeapArray {
public:
    HeapArray(HeapArray& other);

    Heap* heaps[4];
    bool adjusted[4];
    s32 primaryIndex;
};

class HeapPolicy {
public:
    HeapPolicy();

    Heap* parent;
    u32 size;
    u32 createSlack;
    u32 adjustSlack;
    u8 adjust;
    u8 temporary;
    u8 dontCreate;
};

class HeapPolicies {
public:
    HeapPolicy policies[4];
    s32 primaryIndex;
};

}
