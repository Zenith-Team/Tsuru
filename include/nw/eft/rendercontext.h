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

    TextureSampler textureSampler;
    TextureSampler textureSampler2;
    BlendType blendType;
    ZBufATestType zBufATestType;
};

static_assert(sizeof(RenderContext) == 0x20, "nw::eft::RenderContext size mismatch");

} }
