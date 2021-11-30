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
    , nodeTex("tsuru/uhhuh.gtx")
{ }

void Atlys::Renderer::makeLayers() {
    this->layerRenderer.init(2, 512, 5, 5, nullptr);

    // These are also required for levels because it will crash when it tries to access layers with these IDs, since it assumes CourseSelectTask made them
    agl::lyr::Renderer::instance()->createLayer<RenderObjLayer>(Atlys::Renderer::LayerID_Map, "Map", agl::lyr::DisplayType_TopTV, nullptr);
    agl::lyr::Renderer::instance()->createLayer<RenderObjLayer>(Atlys::Renderer::LayerID_Actor, "Actors", agl::lyr::DisplayType_TopTV, nullptr)->setParentRenderer(&this->layerRenderer);
}

void Atlys::Renderer::init() {
    for (u32 i = 0; i < Atlys::Scene::instance()->map->info->layerCount; i++) {
        Atlys::Scene::instance()->map->layers[i].gtx.load(Atlys::Scene::instance()->map->layers[i].gtxName);
    }
}

void Atlys::Renderer::activate() {
    this->bindDrawMethods();
}

void Atlys::Renderer::bindDrawMethods() {
    BIND_DRAW_METHOD(drawMethodMap, "Map", &Atlys::Renderer::drawLayerMap, Atlys::Renderer::LayerID_Map);
    BIND_DRAW_METHOD(drawMethodActors, "Actors", &Atlys::Renderer::drawLayerActors, Atlys::Renderer::LayerID_Actor);
}

void Atlys::Renderer::drawLayerMap(const agl::lyr::RenderInfo& renderInfo) {
    //* Render layers
    for (u32 i = 0; i < Atlys::Scene::instance()->map->info->layerCount; i++) {
        agl::utl::ImageFilter2D::drawTextureMSAA(Atlys::Scene::instance()->map->layers[i].gtx.texture, *renderInfo.viewport, Vec2f(1.0f), Vec2f(0.0f));
    }

    //* Render nodes
    for (u32 i = 0; i < Atlys::Scene::instance()->map->info->nodeCount; i++) {
        Vec2f nodePos2D(0.0f); nodePos2D.x = Atlys::Scene::instance()->map->nodes[i].position.x; nodePos2D.y = Atlys::Scene::instance()->map->nodes[i].position.y;
        agl::utl::ImageFilter2D::drawTextureMSAA(this->nodeTex.texture, *renderInfo.viewport, Vec2f(0.5f), nodePos2D);
    }
    

    //* Render player
    Vec2f playerPos2D(0.0f); playerPos2D.x = Atlys::Scene::instance()->player->position.x; playerPos2D.y = Atlys::Scene::instance()->player->position.y;
    agl::utl::ImageFilter2D::drawTextureMSAA(Atlys::Scene::instance()->player->tex.texture, *renderInfo.viewport, Vec2f(0.05f), playerPos2D);
}

void Atlys::Renderer::drawLayerActors(const agl::lyr::RenderInfo& renderInfo) {
    agl::lyr::Layer* layer = agl::lyr::Renderer::instance()->layers.buffer[0];
    if (Atlys::Renderer::LayerID_Actor < agl::lyr::Renderer::instance()->layers.size)
        layer = agl::lyr::Renderer::instance()->layers.buffer[Atlys::Renderer::LayerID_Actor];

    DrawMgr::instance()->setTargetLayer(layer, 1);

    ActorMgr::instance()->drawActors();

    DrawMgr::instance()->resetTargetLayer();
}
