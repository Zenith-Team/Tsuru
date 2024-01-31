#include "heap/seadSeparateHeap.h"
#include "heap/seadUnitHeap.h"
#include "heap/seadFrameHeap.h"
#include "heap/seadExpHeap.h"

namespace sead {

const void* UnitHeap::getStartAddress() const {
    return mStart;
}

const void* SeparateHeap::getStartAddress() const {
    return mStart;
}

size_t ExpHeap::getSize() const {
    return mSize;
}

size_t FrameHeap::getSize() const {
    return mSize;
}

size_t UnitHeap::getSize() const {
    return mSize;
}

}
