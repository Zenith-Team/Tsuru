#ifndef SEAD_CRITICAL_SECTION_H_
#define SEAD_CRITICAL_SECTION_H_

#include "cafe.h"

#include "sead/heap/seadDisposer.h"

namespace sead {

class CriticalSection : public IDisposer
{
public:
    CriticalSection();

private:
    CriticalSection(const CriticalSection&);
    const CriticalSection& operator=(const CriticalSection&);

public:
    virtual ~CriticalSection();

    void lock();
    bool tryLock();
    void unlock();

protected:
    OSMutex mMutexInner;
};

} // namespace sead

#endif // SEAD_CRITICAL_SECTION_H_
