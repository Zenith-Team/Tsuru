#pragma once

#include "sead/camera.h"
#include "sead/controller.h"
#include "agl/texturesampler.h"
#include "agl/shader.h"

namespace agl { namespace utl {

class DevTools {
public:
    static void controlCamera(sead::LookAtCamera camera, const sead::Controller& controller);
    
    static u32 drawTextureTexCoord(const TextureSampler& texture, const Mtx34& quadMtxSRT, const Mtx44& viewProjMtx, const Vec2f& texCoordScale = Vec2f(1.0f), f32 texCoordRotation = 0.0f, const Vec2f& texCoordTranslation = Vec2f(0.0f), ShaderMode shaderMode = (ShaderMode) 3);
};

} }
