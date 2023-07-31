#pragma once

#include "types.h"

namespace sead {

class FreeList {
public:
    FreeList()
        : free(nullptr)
        , work(nullptr)
    { }

    void init(void* workV, s32 elemSize, s32 num) {
        // SEAD_ASSERT(workV);
        // SEAD_ASSERT(elemSize > 0 && elemSize % 4 == 0);
        // SEAD_ASSERT(num > 0);

        const s32 idxMultiplier = elemSize / 4;

        free = workV;

        for (s32 i = 0; i < num - 1; ++i)
            static_cast<void**>(workV)[idxMultiplier * i] = &static_cast<void**>(workV)[idxMultiplier * (i + 1)];

        static_cast<void**>(workV)[(num - 1) * idxMultiplier] = nullptr;

        work = workV;
    }

    void* get() {
        if (free == nullptr)
            return nullptr;

        void* ptr = free;
        free = *static_cast<void**>(free);
        return ptr;
    }

    void cleanup() {
        free = nullptr;
        work = nullptr;
    }

    //void* work() const { return work; }

    void put(void* ptr) {
        *static_cast<void**>(ptr) = free;
        free = ptr;
    }

    void* free;
    void* work;
};

}
