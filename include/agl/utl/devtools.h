#pragma once

#include "sead/camera.h"
#include "sead/controller.h"
#include "agl/texturesampler.h"
#include "agl/shader.h"

namespace agl { namespace utl {

class DevTools {
public:
    static void controlCamera(sead::LookAtCamera camera, const sead::Controller& controller);
    
    static u32 drawTextureTexCoord(const TextureSampler& texture, const Mtx34& quadMtxSRT, const Mtx44& viewProjMtx, const Vec2f& texCoordScale, f32 texCoordRotation, const Vec2f& texCoordTranslation, ShaderMode shaderMode = (ShaderMode) 3);
};

} }
