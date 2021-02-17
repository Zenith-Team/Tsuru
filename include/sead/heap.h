#pragma once

#include <stddef.h>

#include "list.h"
#include "idisposer.h"
#include "bitflag.h"
#include "inamable.h"
#include "runtimetypeinfo.h"
#include "string.h"
#include "criticalsection.h"

namespace sead { namespace hostio {

class Context;

} // namespace sead::hostio

class Heap : public IDisposer, public INamable
{
public:
    enum HeapDirection
    {
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

    virtual void dump() const
    {
    }

    virtual void genInformation_(hostio::Context*)
    {
    }

    void appendDisposer_(IDisposer* disposer);
    void removeDisposer_(IDisposer* disposer);
    Heap* findContainHeap_(const void* ptr);

    inline void* alloc(size_t size, s32 alignment)
    {
        return tryAlloc(size, alignment);
    }

    typedef OffsetList<Heap> HeapList;
    typedef OffsetList<IDisposer> DisposerList;

    void *mStart;
    size_t mSize;
    Heap* mParent;
    HeapList mChildren;
    ListNode mListNode;
    DisposerList mDisposerList;
    HeapDirection mDirection;
    CriticalSection mCS;
    BitFlag32 mFlag;
};

}
