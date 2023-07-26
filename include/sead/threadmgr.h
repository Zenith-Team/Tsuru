#pragma once

#include "sead/thread.h"
#include "sead/threadlocalstorage.h"

namespace sead {

class ThreadMgr
{
    SEAD_SINGLETON_DISPOSER(ThreadMgr);

public:
    ThreadMgr();
    virtual ~ThreadMgr();

    void initialize(Heap* heap);
    void destroy();

    //bool isMainThread() const { return getCurrentThread() == mainThread; };
    Thread* getMainThread() const { return mainThread; }
    //Thread* getCurrentThread() const { return reinterpret_cast<Thread*>(threadPtrTLS.getValue()); }

    Thread::List list;
    Thread* mainThread;
    ThreadLocalStorage threadPtrTLS;
};
static_assert(sizeof(ThreadMgr) == 0x28);

}