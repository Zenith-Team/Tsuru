#pragma once

#include "sead/heap.h"
#include "sead/heapmgr.h"

extern sead::ExpHeap* TsuruHeap;

class ScopedHeapSetter {
public:
    ScopedHeapSetter(sead::Heap* heap) {
        this->prev = sead::HeapMgr::instance()->getCurrentHeap();
        sead::HeapMgr::instance()->setCurrentHeap(heap);
    }

    ~ScopedHeapSetter() {
        sead::HeapMgr::instance()->setCurrentHeap(this->prev);
    }

private:
    sead::Heap* prev;
};
