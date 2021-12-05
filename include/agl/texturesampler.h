#pragma once

#include "types.h"
#include "agl/texturedata.h"
#include "sead/color.h"
#include "sead/bitflag.h"

namespace agl {

class TextureSampler { // Size: 0x1A0
public:
    TextureSampler();
    TextureSampler(const TextureData& textureData);

    virtual ~TextureSampler();

    // @param location Either const agl::ShaderLocation& or const agl::SamplerLocation&, I don't know which
    u32 activate(void* location);

    void applyTextureData_(const TextureData& data);

    void applyTextureData(const TextureData& data) {
        if (!this->isTexValid ||
                this->textureData.surface.dimension != data.surface.dimension ||
                this->textureData.surface.width     != data.surface.width ||
                this->textureData.surface.height    != data.surface.height ||
                this->textureData.surface.depth     != data.surface.depth ||
                this->textureData.surface.numMips   != data.surface.numMips ||
                this->textureData.surface.format    != data.surface.format ||
                this->textureData.surface.swizzle   != data.surface.swizzle ||
                this->textureData.surface.tile      != data.surface.tile ||
                this->textureData.surface.aa        != data.surface.aa) {
            applyTextureData_(data);
        } else {
            this->textureData.surface.imageData = data.surface.imageData;
            this->textureData.surface.mipData   = data.surface.mipData;

            this->texture.surface.imageData = this->textureData.surface.imageData;
            this->texture.surface.mipData   = this->textureData.surface.mipData;
        }
    }

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
    u32 wrapX;
    u32 wrapY;
    u32 wrapZ;
    sead::Color4f borderColor;
    f32 minLOD;
    f32 maxLOD;
    f32 LODBias;
    u32 maxAnisoRatio;
    bool overrideCompSel;
    u32 redComp;
    u32 greenComp;
    u32 blueComp;
    u32 alphaComp;
    bool isTexValid;
    u8 _E9;
    u8 _EA;
    u32 depthCompare;
    GX2Sampler sampler;
    GX2Texture texture;
    bool hasBorder;
    sead::BitFlag8 flags;
};

static_assert(sizeof(TextureSampler) == 0x1A0, "agl::TextureSampler size mismatch");

}
