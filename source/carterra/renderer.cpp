#include "tsuru/carterra/renderer.h"
#include "tsuru/carterra/camera.h"
#include "agl/lyr/renderer.h"
#include "game/graphics/layer/renderobjlayer.h"
#include "game/actor/actormgr.h"
#include "log.h"

crt::Renderer::Renderer()
    : renderer("CarterraRenderer")
    , drawMethod()
{ }

void crt::Renderer::init(Camera* cam) {
    this->renderer.init(1, 0x300, 5, 5, nullptr);

    agl::lyr::Renderer* layerRenderer = agl::lyr::Renderer::instance();

    layerRenderer->createLayer<RenderObjLayer>(7, "CarterraLayer", agl::lyr::DisplayType_TopTV, nullptr)->setParentRenderer(&this->renderer);

    layerRenderer->layers[7]->camera = &cam->camera;
    layerRenderer->layers[7]->projection = &cam->projection;
}

void crt::Renderer::start() {
    BIND_DRAW_METHOD(this->drawMethod, "Actors", &crt::Renderer::drawLayerActors, 7, this);
}

void crt::Renderer::drawLayerActors(const agl::lyr::RenderInfo& renderInfo) {
    DrawMgr::instance()->setTargetLayer(agl::lyr::Renderer::instance()->layers[7], 1);
    ActorMgr::instance()->drawActors();
    DrawMgr::instance()->resetTargetLayer();
}
