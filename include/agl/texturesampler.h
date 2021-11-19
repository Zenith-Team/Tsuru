#pragma once

#include <types.h>
#include <agl/texturedata.h>

namespace agl {

class TextureSampler { // Size: 0x1A0
public:
    TextureSampler();
    TextureSampler(const TextureData& textureData);

    virtual ~TextureSampler();

    // @param location Either const agl::ShaderLocation& or const agl::SamplerLocation&, I don't know which
    u32 activate(void* location);

    void applyTextureData_(const TextureData& data);

    void initBorderColor_() const;
    void initDepthComp_() const;
    void initFilter_() const;
    void initMipParam_() const;
    void initTexture_() const;
    void initWrap_() const;
    
    void initRegs_() const;

    TextureData textureData;
    u32 magFilter;
    u32 minFilter;
    u32 mipFilter;
    u32 clampX;
    u32 clampY;
    u32 clampZ;
    f32 samplerUnitNumber;
    f32 red;
    f32 green;
    f32 blue;
    f32 minLOD;
    f32 maxLOD;
    f32 LODBias;
    u32 maxAnisoRatio;
    u8 _D4;
    u32 _D8;
    u32 _DC;
    u32 _E0;
    u32 _E4;
    u8 _E8;
    u8 _E9;
    u8 _EA;
    u32 depthCompare;
    GX2Sampler sampler;
    GX2Texture* texturePtr;
    u8 _100[32]; // Unknown values
    void* imagePtr;
    u8 _124[4]; // Unknown values
    void* mipPtr;
    u8 _12C[84]; // Unknown values
    bool hasBorder;
    s8 _199;
};

}
