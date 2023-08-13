#pragma once

#include "types.h"
#include "dynlibs/os/functions.h"

namespace sead {

class ThreadLocalStorage {
public:
    ThreadLocalStorage();

    void* getValue() const {
        return OSGetThreadSpecific(threadLocalStorageInner);
    }
    
    void setValue(void* value) {
        OSSetThreadSpecific(threadLocalStorageInner, value);
    }

    s32 threadLocalStorageInner;
};

static_assert(sizeof(ThreadLocalStorage) == 0x4, "sead::ThreadLocalStorage size mismatch");

}
