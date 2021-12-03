#pragma once

#include "sead/viewport.h"
#include "agl/texturesampler.h"
#include "agl/shader.h"

namespace agl { namespace utl {

class ImageFilter2D {
public:
    static u32 drawTextureMSAA(const TextureSampler& textureSampler, const sead::Viewport& viewport, const sead::Vec2f& scale, const sead::Vec2f& translate, u32 shaderMode = 3);
};

} }
