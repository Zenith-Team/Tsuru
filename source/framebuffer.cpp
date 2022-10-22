#include "agl/lyr/renderer.h"
#include "sead/viewport.h"
#include "agl/renderbuffer.h"
#include "sead/color.h"
#include "game/effect/ptclmgr.h"
#include "agl/lyr/renderinfo.h"
#include "agl/renderbuffer.h"

namespace agl { namespace lyr {

bool Renderer::drawCustomTV(DisplayType displayType) const {
    if (this->gpuCounter % this->gpuCounterPeriod)
        return false;

    if (this->flags.isOffBit(4) && this->flags.isOffBit(0)) {
        agl::RenderBuffer* tvBuffer = this->renderBuffers[DisplayType_TopTV];

        if (tvBuffer) {
            u32 clearFlags = 1;
            if (tvBuffer->targetDepth)
                clearFlags = 3;

            tvBuffer->bind();

            sead::Viewport viewport(*tvBuffer);
            viewport.apply(*tvBuffer);

            tvBuffer->clear(clearFlags, sead::colorBlack, 1.0f, 0);
        }

        this->flags.resetBit(8);
    }

    return this->draw(displayType);
}

bool Renderer::drawCustomDRC(DisplayType displayType) const {
    if (this->gpuCounter % this->gpuCounterPeriod)
        return false;

    if (this->flags.isOffBit(4) && this->flags.isOffBit(0)) {
        agl::RenderBuffer* drcBuffer = this->renderBuffers[DisplayType_BottomDRC];

        if (drcBuffer) {
            u32 clearFlags = 1;
            if (drcBuffer->targetDepth)
                clearFlags = 3;

            drcBuffer->bind();

            sead::Viewport viewport(*drcBuffer);
            viewport.apply(*drcBuffer);

            drcBuffer->clear(clearFlags, sead::colorBlack, 1.0f, 0);
        }

        this->flags.resetBit(8);
    }

    return this->draw(displayType);
}

} }

class DistorterFixer {
public:
    static DistorterFixer instance;
    static agl::lyr::DrawMethodImpl<DistorterFixer> drawMethod;
    agl::TextureSampler textureSampler;

    void fixDistortion(const agl::lyr::RenderInfo& renderInfo) {
        textureSampler.applyTextureData(*reinterpret_cast<agl::TextureData*>(static_cast<agl::RenderBuffer*>(renderInfo.frameBuffer)->targetColors[0]));
        PtclMgr::instance()->setFrameBufferTexture(textureSampler);
    }
};

DistorterFixer DistorterFixer::instance;
agl::lyr::DrawMethodImpl<DistorterFixer> DistorterFixer::drawMethod;

void addDistorterFixer() {
    DistorterFixer::drawMethod.priority = 999999;
    BIND_DRAW_METHOD_TO_RENDERSTEP(DistorterFixer::drawMethod, "DistorterFixer", &DistorterFixer::fixDistortion, 0x7, &DistorterFixer::instance, 3);
}
