#include "tsuru/atlys/renderer.h"
#include "tsuru/atlys/scene.h"
#include "tsuru/atlys/map.h"
#include "log.h"
#include "game/actor/actormgr.h"
#include "game/graphics/drawmgr.h"
#include "agl/utl/imagefilter2d.h"
#include "agl/lyr/renderinfo.h"
#include "agl/texturedatainitializer.h"
#include "sead/filedevicemgr.h"
#include "sead/filedevice.h"
#include "sead/new.h"

Atlys::Renderer::Renderer()
    : layerRenderer("Atlys")
    , drawMethodMap()
    , drawMethodActors()
{ }

void Atlys::Renderer::makeLayers() {
    this->layerRenderer.init(2, 512, 5, 5, nullptr);

    // These are also required for levels because it will crash when it tries to access layers with these IDs, since it assumes CourseSelectTask made them
    agl::lyr::Renderer::instance()->createLayer<RenderObjLayer>(Atlys::Renderer::LayerID_Map, "Map", agl::lyr::DisplayType_TopTV, nullptr);
    agl::lyr::Renderer::instance()->createLayer<RenderObjLayer>(Atlys::Renderer::LayerID_Actor, "Actors", agl::lyr::DisplayType_TopTV, nullptr);
}

void Atlys::Renderer::loadMapTextures() {
    for (u32 i = 0; i < Atlys::Scene::instance()->map->info->layerCount; i++) {
        sead::SafeString texture = Atlys::Scene::instance()->map->layers[i].gtxName;
        Atlys::Scene::instance()->map->layers[i].load(texture);
    }
}

void Atlys::Renderer::init() {
    this->makeDrawMethods();
}

void Atlys::Renderer::makeDrawMethods() {
    MAKE_DRAW_METHOD(drawMethodMap, "Map", &Atlys::Renderer::drawLayerMap, Atlys::Renderer::LayerID_Map);
    MAKE_DRAW_METHOD(drawMethodActors, "Actors", &Atlys::Renderer::drawLayerActors, Atlys::Renderer::LayerID_Actor);
}

void Atlys::Renderer::drawLayerMap(const agl::lyr::RenderInfo& renderInfo) {
    for (u32 i = 0; i < Atlys::Scene::instance()->map->info->layerCount; i++) {
        if (Atlys::Scene::instance()->map->layers[i].sampler.isTexValid)
            agl::utl::ImageFilter2D::drawTextureMSAA(Atlys::Scene::instance()->map->layers[i].sampler, *renderInfo.viewport, Vec2f(1.0f), Vec2f(), 3);
    }
}

void Atlys::Renderer::drawLayerActors(const agl::lyr::RenderInfo& renderInfo) {
    ActorMgr::instance()->drawActors();
}