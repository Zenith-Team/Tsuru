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

class CurrentHeapSetter {
public:
    explicit CurrentHeapSetter(Heap* heap) {
        if (heap) {
            this->setPreviousHeap_(HeapMgr::instance()->getCurrentHeap());
            HeapMgr::instance()->setCurrentHeap(heap);
        } else {
            this->setPreviousHeapToNone_();
        }
    }

    ~CurrentHeapSetter() {
        if (this->hasPreviousHeap_())
            HeapMgr::instance()->setCurrentHeap(this->getPreviousHeap_());
    }

protected:
    Heap* getPreviousHeap_() const { return reinterpret_cast<Heap*>(previousHeap); }

    void setPreviousHeap_(Heap* heap) { previousHeap = reinterpret_cast<uintptr_t>(heap); }
    void setPreviousHeapToNone_() { previousHeap = 1; }

    bool hasPreviousHeap_() const { return reinterpret_cast<Heap*>(previousHeap) != reinterpret_cast<Heap*>(1); }

    uintptr_t previousHeap;
};

}
