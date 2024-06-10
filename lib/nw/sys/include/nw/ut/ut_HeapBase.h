#pragma once

#include <nw/ut/ut_LinkList.h>

namespace nw { namespace ut {

class HeapNode
{
public:
    HeapNode() {}
    virtual ~HeapNode() {}

public:
    LinkListNode linkNode;
};

class HeapBase : public HeapNode
{
public:
    //typedef ut::LinkList<HeapBase, offsetof(HeapNode, linkNode)> HeapList;
    typedef ut::internal::LinkListImpl HeapList;

    static const int DEFAULT_ALIGNMENT = 4;

    static const u32 EXPHEAP_SIGNATURE = 'EXPH';
    static const u32 FRMHEAP_SIGNATURE = 'FRMH';
    static const u32 UNTHEAP_SIGNATURE = 'UNTH';

    static const int OPT_0_CLEAR        = ( 1 << 0 );
    static const int OPT_DEBUG_FILL     = ( 1 << 1 );
    static const int OPT_THREAD_SAFE    = ( 1 << 2 );

    static const int ERROR_PRINT = ( 1 << 0 );

    enum FillType {
        HEAP_FILL_NOUSE,
        HEAP_FILL_ALLOC,
        HEAP_FILL_FREE,
        HEAP_FILL_MAX
    };

    enum HeapType {
        HEAP_TYPE_EXP,      // Expanded heap.
        HEAP_TYPE_FRM,      // Frame heap.
        HEAP_TYPE_UNIT,     // Unit heap.
        HEAP_TYPE_UNKNOWN   // Unknown heap.
    };

    static HeapBase* FindContainHeap(const void* memBlock);
    static HeapBase* FindParentHeap(const HeapBase* heap);

    void* GetHeapStartAddress() { return this; }
    void* GetHeapEndAddress()   { return heapEnd; }

    s32 GetTotalSize()          { return ((s32)(heapEnd) - (s32)(this)); }
    s32 GetTotalUsableSize()    { return ((s32)(heapEnd) - (s32)(heapStart)); }

    u32 SetFillValue(FillType type, u32 val);
    u32 GetFillValue(FillType type);

    HeapType GetHeapType();

protected:
    static const int MIN_ALIGNMENT = 4;

    void Initialize(u32 signature, void* start, void* end, u16 optFlag);
    void Finalize();

    u32 GetSignature() const { return signature; }
    void* GetHeapStart() const { return heapStart; }
    void* GetHeapEnd() const { return heapEnd; }

    void LockHeap();
    void UnlockHeap();

    void FillFreeMemory(void* address, u32 size);
    void FillNoUseMemory(void* address, u32 size);
    void FillAllocMemory(void* address, u32 size);

    void* heapStart; // Heap start address.
    void* heapEnd;   // Heap end (+1) address.

private:
    static HeapBase* FindContainHeap(HeapList* pList, const void* memBlock);
    static HeapList* FindListContainHeap(HeapBase* pHeapBase);

    u16 GetOptionFlag();
    void SetOptionFlag(u16 optFlag);

    u32 signature;
    HeapList childList;
    u32 attribute; // Attribute: [8:Option flag]
};

} }
