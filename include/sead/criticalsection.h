#pragma once

#include "dynamic_libs/os_types.h"
#include "idisposer.h"

namespace sead {

class CriticalSection : public IDisposer
{
public:
    CriticalSection();
    virtual ~CriticalSection();

    void lock();
    bool tryLock();
    void unlock();

    OSMutex mCriticalSectionInner;
};

}
