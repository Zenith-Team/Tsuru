#ifndef SEAD_ARENA_H_
#define SEAD_ARENA_H_

#include "sead/basis/seadTypes.h"

namespace sead {

class Arena
{
public:
    Arena();
    ~Arena();

    u8* initialize(size_t size);
    void destroy();

    u8* getStartAddr() { return mStart; }
    size_t getSize() const { return mSize; }
    bool isInclude(void* ptr) const { return mStart <= ptr && ptr < mStart + mSize; }

protected:
    u8* mStart;
    size_t mSize;
    bool mInitWithStartAddress;
};

} // namespace sead

#endif // SEAD_ARENA_H_
