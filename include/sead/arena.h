#pragma once

#include "types.h"

namespace sead {

class Arena {
public:
    u8* initialize(u32 size);

    u8* start;
    u32 size;
    bool initWithStartAddress;
};

}
