#include "tsuru/heap.h"

sead::ExpHeap* TsuruHeap = nullptr;

void createTsuruHeap() {
    TsuruHeap = sead::ExpHeap::tryCreate(0x27A8000, "TsuruHeap", nullptr, sead::Heap::HeapDirection_Forward, false);
}
