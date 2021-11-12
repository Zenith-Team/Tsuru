#pragma once

#include "types.h"

namespace sead {

class GraphicsContext {
public:
    GraphicsContext();

    void apply();

    u8 _0;
    u8 _1;
    u32 _4;
    u32 _8;
    u8 _C;
    // TODO: I'll do this later

    virtual void vfC(); // deleted
};

}
