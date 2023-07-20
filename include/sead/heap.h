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
        HeapDirection_Forward = 1,
        HeapDirection_Reverse = -1
    };

    Heap(const SafeString& name, Heap* parent, void* address, u32 size, HeapDirection direction, bool);
    virtual ~Heap();

    SEAD_RTTI_BASE(Heap);

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
    virtual u32 getMaxAllocatableSize(s32 alignment) const = 0;
    virtual bool isInclude(const void*) const = 0;
    virtual bool isFreeable() const = 0;
    virtual bool isResizable() const = 0;
    virtual bool isAdjustable() const = 0;

    virtual void dump() const { }

    virtual void genInformation_(hostio::Context*) { }

    void appendDisposer_(IDisposer* disposer);
    void removeDisposer_(IDisposer* disposer);
    Heap* findContainHeap_(const void* ptr);

    void* start;
    size_t size;
    Heap* parent;
    OffsetList<Heap> children;
    ListNode listNode;
    OffsetList<IDisposer> disposerList;
    HeapDirection direction;
    CriticalSection CS;
    BitFlag<u32> flag;
};

class ExpHeap : public Heap {
    SEAD_RTTI_OVERRIDE(ExpHeap, Heap);

public:
    ExpHeap(const SafeString& name, Heap* parent, void* start, u32 size, HeapDirection direction, bool enableLock);

    void doCreate();
    void createMaxSizeFreeMemBlock_();

    static ExpHeap* tryCreate(void* address, u32 size, const SafeString& name, bool enableLock);
    static ExpHeap* tryCreate(u32 size, const SafeString& name, Heap* parent, HeapDirection direction, bool enableLock);
};

class FreeList {
public:
    void* free;
    void* work;
};

class UnitHeap : public Heap {
    SEAD_RTTI_OVERRIDE(UnitHeap, Heap);

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
    virtual u32 getMaxAllocatableSize(s32) const;
    virtual bool isInclude(const void*) const;
    virtual bool isFreeable() const;
    virtual bool isResizable() const;
    virtual bool isAdjustable() const;

    // Creates a heap with the specified parameters
    // @param blockSize The size of each block in the heap
    // @param blockNum The number of blocks to create
    // @param name The name of the heap
    // @param s32 Unknown. Possibly alignment?
    // @param parent The parent heap to create the heap in
    // @param bool Set to false if unsure
    // @return A pointer to the created heap
    static UnitHeap* tryCreateWithBlockNum(u32 blockSize, u32 blockNum, const SafeString& name, s32, Heap* parent, bool enableLock);

    u32 blockSize;
    void* areaStart;
    u32 areaSize;
    u32 freeSize;
    FreeList freeList;
};

class FrameHeap : public Heap {
    SEAD_RTTI_OVERRIDE(FrameHeap, Heap);
};

}
