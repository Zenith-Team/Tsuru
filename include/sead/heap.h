#pragma once

#include "sead/list.h"
#include "sead/bitflag.h"
#include "sead/inamable.h"
#include "sead/idisposer.h"
#include "sead/safestring.h"
#include "sead/criticalsection.h"
#include "sead/runtimetypeinfo.h"

namespace sead { namespace hostio {

class Context;

}

class Heap : public IDisposer, public INamable {
public:
    enum HeapDirection {
        cHeapDirection_Forward = 1,
        cHeapDirection_Reverse = -1
    };

    Heap(const SafeString& name, Heap* parent, void* address, u32 size, HeapDirection direction, bool);
    virtual ~Heap();

    SEAD_RTTI_BASE(Heap)

    virtual void destroy() = 0;
    virtual u32 adjust() = 0;
    virtual void* tryAlloc(size_t size, s32 alignment) = 0;
    virtual void free(void* ptr) = 0;
    virtual void* resizeFront(void*, size_t) = 0;
    virtual void* resizeBack(void*, size_t) = 0;
    virtual void freeAll() = 0;
    virtual u32 getStartAddress() const = 0;
    virtual u32 getEndAddress() const = 0;
    virtual u32 getSize() const = 0;
    virtual u32 getFreeSize() const = 0;
    virtual u32 getMaxAllocatableSize(int) const = 0;
    virtual bool isInclude(const void*) const = 0;
    virtual bool isFreeable() const = 0;
    virtual bool isResizable() const = 0;
    virtual bool isAdjustable() const = 0;

    virtual void dump() const { }

    virtual void genInformation_(hostio::Context*) { }

    void appendDisposer_(IDisposer* disposer);
    void removeDisposer_(IDisposer* disposer);
    Heap* findContainHeap_(const void* ptr);

    inline void* alloc(size_t size, s32 alignment) {
        return tryAlloc(size, alignment);
    }

    void* mStart;
    size_t mSize;
    Heap* mParent;
    OffsetList<Heap> mChildren;
    ListNode mListNode;
    OffsetList<IDisposer> mDisposerList;
    HeapDirection mDirection;
    CriticalSection mCS;
    BitFlag<u32> mFlag;
};

class FreeList {
public:
    void* mFree;
    void* mWork;
};

class UnitHeap : public Heap {
    SEAD_RTTI_OVERRIDE(UnitHeap, Heap)

public:
    UnitHeap(const SafeString& name, Heap* parent, void* address, u32 size, u32, bool);
    virtual ~UnitHeap();

    virtual void destroy();
    virtual u32 adjust();
    virtual void* tryAlloc(size_t size, s32 alignment);
    virtual void free(void* ptr);
    virtual void* resizeFront(void*, size_t);
    virtual void* resizeBack(void*, size_t);
    virtual void freeAll();
    virtual u32 getStartAddress() const;
    virtual u32 getEndAddress() const;
    virtual u32 getSize() const;
    virtual u32 getFreeSize() const;
    virtual u32 getMaxAllocatableSize(int) const;
    virtual bool isInclude(const void*) const;
    virtual bool isFreeable() const;
    virtual bool isResizable() const;
    virtual bool isAdjustable() const;

    u32 mBlockSize;
    void* mAreaStart;
    u32 mAreaSize;
    u32 mFreeSize;
    FreeList mFreeList;
};

}
