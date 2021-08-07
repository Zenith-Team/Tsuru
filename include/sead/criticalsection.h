#pragma once

#include <sead/idisposer.h>
#include <dynlibs/os/types.h>

namespace sead {

class CriticalSection : public IDisposer {
public:
    CriticalSection();
    virtual ~CriticalSection();

    void lock();
    bool tryLock();
    void unlock();

    OSMutex mCriticalSectionInner;
};

}
