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

    u8 _10[0x44 - 0x10];
    sead::Camera* camera;
    sead::Projection* projection;
    //...
};

//static_assert(sizeof(Layer) == 0x41C, "agl::lyr::Layer size mismatch");

} }
