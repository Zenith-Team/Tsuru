#pragma once

#include "types.h"

namespace sead {

template <typename T>
class BitFlag {
public:
    BitFlag()
        : mBits(0)
    { }

    T mBits;
};

}
