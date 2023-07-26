#pragma once

#include "types.h"
#include "agl/texturedata.h"
#include "sead/color.h"
#include "sead/bitflag.h"
#include "sead/graphics.h"
#include "agl/shaderlocation.h"

namespace agl {

enum TextureFilterType { };
enum TextureMipFilterType { };
enum TextureWrapType { };
enum TextureAnisoRatio { };

class TextureSampler { // Size: 0x1A0
public:
    TextureSampler();
    TextureSampler(const TextureData& textureData);

    virtual ~TextureSampler();

    bool activate(const SamplerLocation& samplerLocation, s32 = -1) const;

    // Custom function
    void setup() const {
        if (this->flags != 0)
            this->initRegs_();
    }

    void applyTextureData(const TextureData& data) {
        if (!this->isTextureSet ||
                this->textureData.surface.dimension != data.surface.dimension ||
                this->textureData.surface.width     != data.surface.width     ||
                this->textureData.surface.height    != data.surface.height    ||
                this->textureData.surface.depth     != data.surface.depth     ||
                this->textureData.surface.numMips   != data.surface.numMips   ||
                this->textureData.surface.format    != data.surface.format    ||
                this->textureData.surface.swizzle   != data.surface.swizzle   ||
                this->textureData.surface.tile      != data.surface.tile      ||
                this->textureData.surface.aa        != data.surface.aa) {
            this->applyTextureData_(data);
        } else {
            this->textureData.surface.imageData = data.surface.imageData;
            this->textureData.surface.mipData   = data.surface.mipData;

            this->texture.surface.imageData = this->textureData.surface.imageData;
            this->texture.surface.mipData   = this->textureData.surface.mipData;
        }
    }

private:
    void applyTextureData_(const TextureData& data);

    void initRegs_() const;

    void initTexture_() const;
    void initWrap_() const;
    void initFilter_() const;
    void initMipParam_() const;
    void initDepthComp_() const;
    void initBorderColor_() const;

public:
    TextureData textureData;
    TextureFilterType magFilter;
    TextureFilterType minFilter;
    TextureMipFilterType mipFilter;
    TextureWrapType wrapX;
    TextureWrapType wrapY;
    TextureWrapType wrapZ;
    sead::Color4f borderColor;
    f32 minLOD;
    f32 maxLOD;
    f32 LODBias;
    TextureAnisoRatio maxAnisoRatio;
    bool overrideCompSel;
    TextureCompSel compR;
    TextureCompSel compG;
    TextureCompSel compB;
    TextureCompSel compA;
    bool isTextureSet;
    u8 _E9;
    bool depthCompareEnable;
    sead::Graphics::DepthFunc depthCompareFunc;
    GX2Sampler sampler;
    GX2Texture texture;
    bool hasBorder;
    sead::BitFlag8 flags;
};

static_assert(sizeof(TextureSampler) == 0x1A0, "agl::TextureSampler size mismatch");

}
