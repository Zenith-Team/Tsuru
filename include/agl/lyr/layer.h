#pragma once

#include <sead.h>
#include <types.h>

#include "drawmethod.h"

namespace agl { namespace lyr {

class Layer : public sead::IDisposer {
public:
    Layer();
    virtual ~Layer();

    DrawMethod* pushBackDrawMethod(u32, DrawMethod* drawMethod);

    // ...

    u8 _10[0x41C - 0x10];
};

} }
