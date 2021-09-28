#pragma once

#include <types.h>
#include <agl/texturedata.h>

namespace agl {

class TextureSampler { // Size: 0x1A0
public:
    TextureSampler();
    TextureSampler(TextureData* textureData);

    TextureData _0;
    u8 _9C[0x1A0 - 0x9C];   // TODO: I'll do this later
};

}
