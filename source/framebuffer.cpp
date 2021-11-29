#include "agl/lyr/renderer.h"
#include "sead/viewport.h"
#include "agl/renderbuffer.h"
#include "sead/color.h"

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
