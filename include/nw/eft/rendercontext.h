#ifndef EFT_RENDER_CONTEXT_H_
#define EFT_RENDER_CONTEXT_H_

#include "nw/eft/cafewrapper.h"
#include "nw/eft/enum.h"

namespace nw { namespace eft {

struct TextureRes;
struct FragmentTextureLocation;

class RenderContext {
public:
    RenderContext();

    void SetupCommonState();
    void SetupBlendType(BlendType blendType);
    void SetupZBufATest(ZBufATestType zBufATestType);
    void SetupDisplaySideType(DisplaySideType displaySideType) const;
    inline void _SetupFragmentTexture(const GX2Texture* texture, const GX2Sampler* sampler, TextureSlot slot, FragmentTextureLocation samplerLocation) const;
    void SetupTexture(const TextureRes* texture, TextureSlot slot, FragmentTextureLocation samplerLocation);
    void SetupTexture(const GX2Texture* texture, TextureSlot slot, FragmentTextureLocation samplerLocation);

    TextureSampler textureSampler;
    TextureSampler textureSampler2;
    BlendType blendType;
    ZBufATestType zBufATestType;
};
static_assert(sizeof(RenderContext) == 0x20, "RenderContext size mismatch");

} } // namespace nw::eft

#endif // EFT_RENDER_CONTEXT_H_
