#pragma once

#include "types.h"

namespace agl {

class IndexStream { // Size: 0x18
public:
    IndexStream();
    virtual ~IndexStream();

    void cleanUp_();
    void setUpStream_(void*, u32 indexStreamFormat, u32);

    u32 _0;
    u32 _4;
    u32 _8;
    u32 _C;
    u32 _10;
};

static_assert(sizeof(IndexStream) == 0x18, "agl::IndexStream size mismatch");

}
