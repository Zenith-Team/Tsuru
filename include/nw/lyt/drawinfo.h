#pragma once

#include "types.h"
#include "nw/math/vec2.h"
#include "nw/math/mtx34.h"
#include "nw/math/mtx44.h"

namespace nw { namespace lyt {

class Layout;

class DrawInfo { // Size: 0xC8
public:
    DrawInfo();
    virtual ~DrawInfo();

    nw::math::MTX44 projMtx;
    nw::math::MTX34 viewMtx;
    nw::math::MTX34 modelViewMtx;
    nw::math::VEC2 locationAdjustScale;
    void* graphicsResource;
    nw::lyt::Layout* layout;
    u8 _B0[20];
};

} }

static_assert(sizeof(nw::lyt::DrawInfo) == 0xC8, "nw::lyt::DrawInfo size mismatch");
