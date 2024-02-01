#include "tsuru/layoutrenderer.h"
#include "framework/seadTaskBase.h"
#include "framework/seadTaskMgr.h"
#include "layer/aglLayer.h"
#include "layer/aglRenderer.h"
#include "layer/aglRenderInfo.h"
#include "tsuru/log.h"

SEAD_SINGLETON_DISPOSER_IMPL(LayoutRenderer);

extern "C" void initLayoutRenderer(sead::TaskBase* layermgr) {
    LayoutRenderer::createInstance(nullptr);

    layermgr->adjustHeapAll();
}

LayoutRenderer::LayoutRenderer() {
    this->drawMethod.bind(this, &LayoutRenderer::render, "LayoutRenderer");
    agl::lyr::Renderer::instance()->getLayer(0xE)->pushBackDrawMethod(&this->drawMethod);

    PRINT("LayoutRenderer initialized");
}

void LayoutRenderer::render(const agl::lyr::RenderInfo& renderInfo) {
    for (u32 i = 0; i < this->layouts.count(); i++) {
        this->layouts[i]->draw(renderInfo.getProjection()->getDeviceProjectionMatrix());
    }

    this->layouts.clear();
}
