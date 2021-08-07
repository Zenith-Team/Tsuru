#pragma once

#include <types.h>

namespace sead {

template <typename T>
class BitFlag {
public:
    BitFlag()
        : mBits(0)
    { }

    T mBits;
};

typedef BitFlag<u32> BitFlag32;

}
