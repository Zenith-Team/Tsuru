#pragma once

#include "types.h"

namespace sead {

template <typename T>
class ScopedLock
{
private:
    ScopedLock(const ScopedLock&);
    ScopedLock& operator=(const ScopedLock&);

public:
    ScopedLock(T& lockV)
        : lock(lockV)
    {
        lock.lock();
    }

    ~ScopedLock()
    {
        lock.unlock();
    }

private:
    T& lock;
};

template <typename T>
class ConditionalScopedLock
{
private:
    ConditionalScopedLock(const ConditionalScopedLock&);
    ConditionalScopedLock& operator=(const ConditionalScopedLock&);

public:
    ConditionalScopedLock(T& lockV, bool doLock)
        : lock(nullptr)
    {
        if (doLock)
        {
            lock = &lockV;
            lock->lock();
        }
    }

    ~ConditionalScopedLock()
    {
        if (lock)
            lock->unlock();
    }

private:
    T* lock;
};

}
