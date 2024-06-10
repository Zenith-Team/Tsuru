#pragma once

#include <nw/snd/snd_SoundMemoryAllocatable.h>
#include <nw/snd/snd_FrameHeap.h>
#include <nw/ut/os/ut_CriticalSection.h>

namespace nw { namespace snd {

class SoundHeap : public SoundMemoryAllocatable
{
public:
    typedef void (*DisposeCallback)(void* mem, unsigned long size, void* userArg);

public:
    SoundHeap();
    virtual ~SoundHeap();

    bool Create(
        void* startAddress,
        size_t size
    );

    void Destroy();

    virtual void* Alloc(size_t size);

    void* Alloc(
        size_t size,
        SoundHeap::DisposeCallback callback,
        void* callbackArg
    );

    void Clear();

    bool IsValid() const { return frameHeap.IsValid(); }

    int SaveState();

    void LoadState(int level);

    int GetCurrentLevel() const
    {
        ut::ScopedLock<ut::CriticalSection> lock(criticalSection);
        return frameHeap.GetCurrentLevel();
    }

    size_t GetSize() const
    {
        ut::ScopedLock<ut::CriticalSection> lock(criticalSection);
        return frameHeap.GetSize();
    }

    size_t GetFreeSize() const
    {
        ut::ScopedLock<ut::CriticalSection> lock(criticalSection);
        return frameHeap.GetFreeSize();
    }

    void Dump(nw::snd::SoundDataManager& mgr, nw::snd::SoundArchive& arc) const
    {
        ut::ScopedLock<ut::CriticalSection> lock(criticalSection);
        frameHeap.Dump(mgr, arc);
    }

private:
    static void DisposeCallbackFunc(void* mem, unsigned long size, void* arg);

    mutable ut::CriticalSection criticalSection;
    internal::FrameHeap frameHeap;
};

} }
