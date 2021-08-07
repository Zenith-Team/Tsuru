#pragma once

#include <nw/eft/cafewrapper.h>
#include <nw/eft/enum.h>

namespace nw { namespace eft {

struct TextureRes;
struct FragmentTextureLocation;

class RenderContext { // Size: 0x20
public:
    RenderContext();

    void SetupCommonState();
    void SetupBlendType(BlendType blendType);
    void SetupZBufATest(ZBufATestType zBufATestType);
    void SetupDisplaySideType(DisplaySideType displaySideType) const;
    inline void _SetupFragmentTexture(GX2Texture* texture, const GX2Sampler* sampler, TextureSlot slot, FragmentTextureLocation samplerLocation) const;
    void SetupTexture(const TextureRes* texture, TextureSlot slot, FragmentTextureLocation samplerLocation);
    void SetupTexture(const GX2Texture* texture, TextureSlot slot, FragmentTextureLocation samplerLocation);

    TextureSampler mTextureSampler;
    TextureSampler mTextureSampler2;
    BlendType mBlendType;
    ZBufATestType mZBufATestType;
};

static_assert(sizeof(RenderContext) == 0x20, "RenderContext size mismatch");

} }
