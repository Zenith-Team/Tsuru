#pragma once

#include "ptrarray.h"

#define NUM_ROOT_HEAPS_MAX         4
#define NUM_INDEPENDENT_HEAPS_MAX  4

namespace sead {

class Heap;

class HeapMgr {
public:
    HeapMgr();
    virtual ~HeapMgr();

    Heap* getCurrentHeap();
    Heap* setCurrentHeap_(Heap* heap);

    static HeapMgr* sInstancePtr;

    typedef FixedPtrArray<Heap,        NUM_ROOT_HEAPS_MAX> RootHeaps;
    typedef FixedPtrArray<Heap, NUM_INDEPENDENT_HEAPS_MAX> IndependentHeaps;

    static RootHeaps sRootHeaps;
    static IndependentHeaps sIndependentHeaps;

    // ...
};

}

#undef NUM_ROOT_HEAPS_MAX
#undef NUM_INDEPENDENT_HEAPS_MAX
