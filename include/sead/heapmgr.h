#pragma once

#include "sead/arena.h"
#include "sead/criticalsection.h"
#include "sead/ptrarray.h"

namespace sead {

class Heap;

class HeapMgr {
public:
    void setCurrentHeap(Heap* heap);
    Heap* getCurrentHeap();

    static void initialize(u32 size);
    static void initialize(Arena* arena);

    static void initializeImpl_();

    static void createRootHeap_();

    static Arena* sArena;
    static Arena sDefaultArena;

    static CriticalSection sHeapTreeLockCS;

    static FixedPtrArray<Heap, 4> sRootHeaps;

protected:
    static HeapMgr sInstance;
    static HeapMgr* sInstancePtr;

public:
    static inline HeapMgr* instance() {
        return sInstancePtr;
    }

    void* allocFailedCallback;
};

}
