#include "tsuru/atlys/renderer.h"
#include "tsuru/atlys/scene.h"
#include "log.h"
#include "game/actor/actormgr.h"

Atlys::Renderer::Renderer()
    : drawMethodMap()
    , drawMethodActors()
{ }

void Atlys::Renderer::makeLayers() {
    // These are also required for levels because it will crash when it tries to access layers with these IDs, since it assumes CourseSelectTask made them
    agl::lyr::Renderer::instance()->createLayer<Atlys::Renderer::Layer>(Atlys::Renderer::LayerID_Map, "Map", 0, nullptr);
    agl::lyr::Renderer::instance()->createLayer<Atlys::Renderer::Layer>(Atlys::Renderer::LayerID_Actor, "Actors", 0, nullptr);
}

void Atlys::Renderer::makeDrawMethods() {
    MAKE_DRAW_METHOD(drawMethodMap, "Map", &Atlys::Renderer::drawLayerMap, Atlys::Renderer::LayerID_Map);
    MAKE_DRAW_METHOD(drawMethodActors, "Actors", &Atlys::Renderer::drawLayerActors, Atlys::Renderer::LayerID_Actor);
}

void Atlys::Renderer::drawLayerMap(const agl::lyr::RenderInfo& renderInfo) {

}

void Atlys::Renderer::drawLayerActors(const agl::lyr::RenderInfo& renderInfo) {
    ActorMgr::instance()->drawActors();
}
