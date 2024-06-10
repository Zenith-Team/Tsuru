#pragma once

#include <nw/ut/ut_ScopedLock.h>
#include <nw/ut/os/ut_Mutex.h>

namespace nw { namespace ut {

class CriticalSection
{
public:
    static const u32 CRITICAL_SECTION_SIZE = 24;
    static const u32 CRITICAL_SECTION_ALIGN = 4;

public:
    CriticalSection()
    {
        mutex.Initialize();
    }

    ~CriticalSection()
    {
        mutex.Finalize();
    }

    void Enter()
    {
        mutex.Lock();
    }

    bool TryEnter()
    {
        return mutex.TryLock();
    }

    void Leave()
    {
        mutex.Unlock();
    }

    void Lock()
    {
        this->Enter();
    }

    bool TryLock()
    {
        return this->TryEnter();
    }

    void Unlock()
    {
        this->Leave();
    }

    ut::Mutex mutex;
};

template <>
class ScopedLock<CriticalSection>
{
private:
    ScopedLock(const ScopedLock&);
    ScopedLock& operator=(const ScopedLock&);

public:
    explicit ScopedLock(CriticalSection& lockObj_)
        : lockObj(lockObj_)
    {
        lockObj.Enter();
    }

    ~ScopedLock()
    {
        lockObj.Leave();
    }

private:
    CriticalSection& lockObj;
};

} }
