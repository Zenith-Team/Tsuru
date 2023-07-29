#pragma once

#include "agl/lght/lightmap.h"

namespace agl { namespace lght {

class LightMapMgr /* : public agl::utl::IParameterIO */ { // Size: 0x2D6C
public:
    LightMapMgr();
    /* virtual */ ~LightMapMgr();

    u8 _0[0x1E0];
    sead::Buffer<LightMap> lightMaps;
    u8 _1E8[0x2D6C - 0x1E8];
};

static_assert(sizeof(LightMapMgr) == 0x2D6C, "agl::lght::LightMapMgr size mismatch");

} }
