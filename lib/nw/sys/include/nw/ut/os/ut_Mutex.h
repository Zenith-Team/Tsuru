#pragma once

#include <types.h>

#include <cafe/os/OSMutex.h>

namespace nw { namespace ut {

class Mutex
{
public:
    Mutex()
        : isIntialized(false)
    {
    }

    ~Mutex()
    {
    }

    void Initialize()
    {
        if (!isIntialized)
        {
            isIntialized = true;
            OSInitMutex(&lock);
        }
    }

    void Finalize()
    {
        isIntialized = false;
    }

    void Lock()
    {
        //NW_ASSERT(isIntialized);
        OSLockMutex(&lock);
    }

    bool TryLock()
    {
        //NW_ASSERT(isIntialized);
        return OSTryLockMutex(&lock) != false;
    }

    void Unlock()
    {
        //NW_ASSERT(isIntialized);
        OSUnlockMutex(&lock);
    }

    OSMutex lock;
    bool isIntialized;
};

} }
