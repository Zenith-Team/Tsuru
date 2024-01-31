#include "layer/aglRenderer.h"
#include "gfx/seadViewport.h"
#include "common/aglRenderBuffer.h"
#include "common/aglRenderTarget.h"
#include "gfx/seadColor.h"
#include "game/effect/ptclmgr.h"
#include "layer/aglRenderInfo.h"
#include "layer/aglDrawMethod.h"
#include "layer/aglLayer.h"

class TsuruAglLyrRenderer : public agl::lyr::Renderer {
    bool drawTV_(agl::lyr::DisplayType displayType) const;
    bool drawDRC_(agl::lyr::DisplayType displayType) const;
};

bool TsuruAglLyrRenderer::drawTV_(agl::lyr::DisplayType displayType) const  {
    if (mGpuCounter % mGpuCounterPeriod)
        return false;

    if (mFlag.isOffBit(4) && mFlag.isOffBit(0)) {
        agl::RenderBuffer* renderBuffer = mRenderBuffer[agl::lyr::cDisplayType_Top_TV];
        if (renderBuffer != nullptr) {
            u32 clearFlag = 1;
            if (renderBuffer->getRenderTargetDepth() != nullptr)
                clearFlag = 3;

            renderBuffer->bind();

            sead::Viewport viewport = sead::Viewport(*renderBuffer);
            viewport.apply(*renderBuffer);

            renderBuffer->clear(
                clearFlag,
                sead::Color4f::cBlack,
                1.0f,
                0
            );
        }

        // Render buffer clear bit
        mFlag.resetBit(8);
    }

    // This must return true
    return this->draw(displayType);
}

bool TsuruAglLyrRenderer::drawDRC_(agl::lyr::DisplayType displayType) const {
    if (mGpuCounter % mGpuCounterPeriod)
        return false;

    if (mFlag.isOffBit(4) && mFlag.isOffBit(0)) {
        agl::RenderBuffer* renderBuffer = mRenderBuffer[agl::lyr::cDisplayType_Bottom_DRC];
        if (renderBuffer != nullptr) {
            u32 clearFlag = 1;
            if (renderBuffer->getRenderTargetDepth() != nullptr)
                clearFlag = 3;

            renderBuffer->bind();

            sead::Viewport viewport = sead::Viewport(*renderBuffer);
            viewport.apply(*renderBuffer);

            renderBuffer->clear(clearFlag, sead::Color4f::cBlack, 1.0f, 0);
        }

        // Render buffer clear bit
        mFlag.resetBit(8);
    }

    // This must return true
    return this->draw(displayType);
}

class DistorterFixer {
public:
    static DistorterFixer instance;
    static agl::lyr::DrawMethod drawMethod;
    
    agl::TextureSampler textureSampler;

    void fixDistortion(const agl::lyr::RenderInfo& renderInfo) {
        textureSampler.applyTextureData(renderInfo.getRenderBuffer()->getRenderTargetColor()->getTextureData());
        PtclMgr::instance()->setFrameBufferTexture(textureSampler);
    }
};

DistorterFixer DistorterFixer::instance;
agl::lyr::DrawMethod DistorterFixer::drawMethod;

void addDistorterFixer() {
    DistorterFixer::drawMethod.setPriority(999999);
    DistorterFixer::drawMethod.bind(&DistorterFixer::instance, &DistorterFixer::fixDistortion, "DistorterFixer");
    agl::lyr::Renderer::instance()->getLayer(7)->pushBackDrawMethod(3, &DistorterFixer::drawMethod);
}
