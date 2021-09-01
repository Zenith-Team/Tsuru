#pragma once

#include <sead.h>

namespace agl { namespace lyr {

class Layer;

class Renderer { // Size: 0xF78
    SEAD_SINGLETON_DISPOSER(Renderer)

public:
    u8 _10[0xDA8-0x10];             // _10
    sead::Buffer<Layer*> mLayers;   // _DA8
    //...
};

} }
