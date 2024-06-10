#pragma once

namespace nw { namespace ut {

template <typename TLockObject>
class ScopedLock
{
private:
    ScopedLock(const ScopedLock&);
    ScopedLock& operator=(const ScopedLock&);

public:
    explicit ScopedLock(TLockObject& lockObj_)
        : lockObj(lockObj_)
    {
        lockObj.Lock();
    }

    ~ScopedLock()
    {
        lockObj.Unlock();
    }

private:
    TLockObject& lockObj;
};

} }
