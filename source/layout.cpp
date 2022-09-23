#include "tsuru/layoutrenderer.h"
#include "agl/lyr/layer.h"
#include "agl/lyr/renderer.h"
#include "agl/lyr/renderinfo.h"
#include "log.h"

SEAD_SINGLETON_DISPOSER_IMPL(LayoutRenderer);

extern "C" void initLayoutRenderer(sead::TaskBase* layermgr) {
    LayoutRenderer::createInstance(nullptr);

    layermgr->adjustHeapAll();
}

LayoutRenderer::LayoutRenderer() {
    BIND_DRAW_METHOD(this->drawMethod, "LayoutRenderer", &LayoutRenderer::render, 0xE, this);

    PRINT("LayoutRenderer initialized");
}

void LayoutRenderer::render(const agl::lyr::RenderInfo& renderInfo) {
    for (u32 i = 0; i < this->layouts.count(); i++) {
        this->layouts[i]->draw(renderInfo.projection->deviceMatrix);
    }

    this->layouts.clear();
}
