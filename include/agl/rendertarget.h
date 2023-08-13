#pragma once

#include "agl/texturedata.h"

namespace agl {

template <typename T>
class RenderTarget {
public:
    RenderTarget();

    void applyTextureData(const TextureData& textureData);
    void applyTextureData(const TextureData& textureData, u32 mipLevel, u32 slice);

protected:
    void applyTextureData_(const TextureData& textureData, u32 mipLevel, u32 slice);

public:
    TextureData textureData;
    mutable bool updateRegs;
    u32 mipLevel;
    u32 slice;
};

static_assert(sizeof(RenderTarget<void>) == 0xA8, "agl::RenderTarget size mismatch");

class RenderTargetColor : public RenderTarget<RenderTargetColor> { // Size: 0x154
public:
    RenderTargetColor();
    RenderTargetColor(const TextureData& texture_Data, u32 mipLevel, u32 slice);

    void invalidateGPUCache() const;
    void bind(s32 targetIdx);

private:
    void initRegs_() const;
    void onApplyTextureData_();

public:
    bool isMSAA2D;
    u32 auxBufferSize;
    u32 auxBufferAlign;
    void* auxBuffer;
    GX2ColorBuffer colorBuffer;
};

static_assert(sizeof(RenderTargetColor) == 0x154, "agl::RenderTargetColor size mismatch");

class RenderTargetDepth : public RenderTarget<RenderTargetDepth> { // Size: 0x160
public:
    RenderTargetDepth();
    RenderTargetDepth(const TextureData& textureData, u32 mipLevel, u32 slice);

    void invalidateGPUCache() const;
    void bind() const;

private:
    void initRegs_() const;
    void onApplyTextureData_();

public:
    u32 hiZBufferSize;
    u32 hiZBufferAlign;
    void* hiZBuffer;
    GX2DepthBuffer depthBuffer;
};

static_assert(sizeof(RenderTargetDepth) == 0x160, "agl::RenderTargetDepth size mismatch");

}

