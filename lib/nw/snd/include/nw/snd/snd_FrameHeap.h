#pragma once

#include <nw/ut/ut_LinkList.h>
#include <nw/ut/ut_FrameHeap.h>
#include <nw/snd/snd_SoundDataManager.h>

namespace nw { namespace snd { namespace internal {

class FrameHeap
{
public:
    typedef void (*DisposeCallback)(void* mem, unsigned long size, void* userArg);

    struct Block
    {
    public:
        Block(void* buffer, u32 size_, DisposeCallback callback_, void* callbackArg_)
            : pBuffer(buffer)
            , size(size_)
            , callback(callback_)
            , callbackArg(callbackArg_)
        {
        }

        ~Block()
        {
            if (callback != NULL)
            {
                callback(pBuffer, size, callbackArg);
            }
        }

        void* GetBufferAddr() { return pBuffer; }
        const void* GetBufferAddr() const { return pBuffer; }
        u32 GetBufferSize() const { return size; }
        DisposeCallback GetDisposeCallback() const { return callback; }
        const void* GetDisposeCallbackArg() const { return callbackArg; }

    public:
        ut::LinkListNode link;
    private:
        void* pBuffer;
        u32 size;
        DisposeCallback callback;
        void* callbackArg;
    };

    //typedef ut::LinkList<Block, offsetof(Block, link)> BlockList;
    typedef ut::internal::LinkListImpl BlockList;

    class Section
    {
    public:
        Section();
        ~Section();

        void AppendBlock(Block* block);
        const BlockList& GetBlockList() const { return blockList; }
        BlockList& GetBlockList() { return blockList; }

        void* GetAddr() { return this; }
        void SetUseCallback(bool use) { useCallback = use; }

        void Dump(nw::snd::SoundDataManager& mgr, nw::snd::SoundArchive& arc) const;

    public:
        ut::LinkListNode link;
    private:
        BlockList blockList;
        bool useCallback;
    };

    //typedef ut::LinkList<Section, offsetof(Section, link)> SectionList;
    typedef ut::internal::LinkListImpl SectionList;

    static const int HEAP_ALIGN = 256;

public:
    FrameHeap();
    ~FrameHeap();

    bool  Create(void* startAddress, u32 size);
    void  Destroy();

    void* Alloc(
        u32 size,
        FrameHeap::DisposeCallback callback,
        void* callbackArg
    );

    void  Clear();

    int   SaveState();
    void  LoadState(int level);
    int   GetCurrentLevel() const;

    u32   GetSize() const;
    u32   GetFreeSize() const;

    bool  IsValid() const { return heap != NULL; }

    void Dump(nw::snd::SoundDataManager& mgr, nw::snd::SoundArchive& arc) const;
    bool ProcessCallback(int level);

private:
    ut::FrameHeap* heap;
    SectionList sectionList;

    bool NewSection();
    void ClearSection();
};

} } }
