#pragma once

#include <nw/ut/ut_HeapBase.h>

namespace nw { namespace ut {

class FrameHeap : public HeapBase
{
public:
    static const int FREE_HEAD = (1 << 0);
    static const int FREE_TAIL = (1 << 1);
    static const int FREE_ALL = (FREE_HEAD | FREE_TAIL);

    struct HeapState
    {
        u32 tagName;
        void* headAllocator;
        void* tailAllocator;
        HeapState* pPrevState;

        HeapState()
            : tagName(0)
            , headAllocator(NULL)
            , tailAllocator(NULL)
            , pPrevState(NULL)
        {
        }
    };

public:
    static  FrameHeap* Create(void* startAddress, u32 heapSize, u16 optFlag = 0);

    void*   Destroy();
    void*   Alloc(u32 size, int alignment = DEFAULT_ALIGNMENT);
    u32     ResizeForMBlock(void* memBlock, u32 newSize);
    u32     GetAllocatableSize(int alignment = DEFAULT_ALIGNMENT);
    void    Free(int mode);
    bool    RecordState(u32 tagName);
    bool    FreeByState(u32 tagName);
    u32     Adjust();

private:
    bool    IsValid() { return GetSignature() == FRMHEAP_SIGNATURE; }

    void*   AllocFromHead(u32 size, int alignment);
    void*   AllocFromTail(u32 size, int alignment);

    void    FreeHead();
    void    FreeTail();

    void* headAllocator;
    void* tailAllocator;
    HeapState* pState;
};

} }
