#pragma once

#include "sead.h"
#include "types.h"

namespace agl { namespace lyr {

class Layer : public sead::IDisposer {  // size: 0x41C
public:
    Layer();
    virtual ~Layer();

    // ...

    u8 _10[0x41C - 0x10];
};

} }
