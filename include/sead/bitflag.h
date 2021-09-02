#pragma once

#include <types.h>

namespace sead {

template <typename T>
class BitFlag {
public:
    BitFlag()
        : bits(0)
    { }

    T bits;
};

typedef BitFlag<u32> BitFlag32;

}
