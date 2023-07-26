#pragma once

#include "types.h"

namespace sead {

class ThreadLocalStorage
{
public:
    ThreadLocalStorage();

    s32 threadLocalStorageInner;
};
static_assert(sizeof(ThreadLocalStorage) == 0x4);

}
