#pragma once

#include "boundbox.h"

namespace sead {

class Viewport : public BoundBox2<f32> { // Size: 0x18
public:
    Viewport(f32, f32, f32, f32);

    void* _10;

    virtual void vfC(); // deleted
};

static_assert(sizeof(Viewport) == 0x18, "sead::Viewport size mismatch");

}
