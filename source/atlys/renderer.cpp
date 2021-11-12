#include "tsuru/atlys.h"
#include "log.h"
#include "sead/filedevice.h"
#include "sead/filedevicemgr.h"

static Vec2f RenderBufferSizeVec(1280.0f, 720.0f);

Atlys::Scene::Renderer::Renderer()
    : backgroundTextureData()
    , backgroundTargetColor()
    , backgroundRenderBuffer(RenderBufferSizeVec, 0.0f, 0.0f, 1280.0f, 720.0f)
{ }

Atlys::Scene::Renderer::~Renderer() {
    if (this->backgroundTextureData.surface.imageData)
        delete this->backgroundTextureData.surface.imageData;
}

void Atlys::Scene::Renderer::init() {

}
