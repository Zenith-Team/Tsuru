#pragma once

#include "agl/texturesampler.h"
#include "sead/safestring.h"

namespace agl { namespace lght {

class LightMapMgr;

class LightMap /* : public agl::env::EnvObjSet */ { // Size: 0x8AC
public:
    LightMap();
    /* virtual */ ~LightMap();

    u8 _0[0x1EC];
    TextureSampler texture;
    u8 _38C[0x8AC - 0x38C];
};

static_assert(sizeof(LightMap) == 0x8AC, "agl::lght::LightMap size mismatch");

} }
