#pragma once

#include <types.h>

namespace sead {

template <typename T>
class BitFlag {
public:
    forceinline BitFlag()
        : bits(0)
    { }

    bool operator==(const BitFlag<T>& rhs) const { return this->bits == rhs.bits; }
    bool operator!=(const BitFlag<T>& rhs) const { return this->bits != rhs.bits; }

    T bits;
};

typedef BitFlag<u8> BitFlag8;
typedef BitFlag<u16> BitFlag16;
typedef BitFlag<u32> BitFlag32;
typedef BitFlag<u64> BitFlag64;

}
