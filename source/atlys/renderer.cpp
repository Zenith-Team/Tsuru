#include "tsuru/atlys/renderer.h"
#include "tsuru/atlys/scene.h"
#include "tsuru/atlys/map.h"
#include "game/actor/actormgr.h"
#include "game/graphics/drawmgr.h"
#include "game/resource/resarchive.h"
#include "game/resource/resmgr.h"
#include "agl/lyr/renderinfo.h"
#include "agl/texturedatainitializer.h"
#include "agl/utl/devtools.h"
#include "sead/matrixcalccommon.h"
#include "sead/filedevicemgr.h"
#include "sead/filedevice.h"
#include "sead/new.h"
#include "math/functions.h"
#include "log.h"

Atlys::Renderer::Renderer()
    : layerRenderer("Atlys")
    , drawMethodMap()
    , drawMethodActors()
{ }

void Atlys::Renderer::makeLayers() {
    this->layerRenderer.init(1, 0x300, 5, 5, nullptr);

    // These are also required for levels because it will crash when it tries to access layers with these IDs, since it assumes CourseSelectTask made them
    agl::lyr::Renderer::instance()->createLayer<RenderObjLayer>(Atlys::Renderer::LayerID_Map, "Map", agl::lyr::DisplayType_TopTV, nullptr);
    agl::lyr::Renderer::instance()->createLayer<RenderObjLayer>(Atlys::Renderer::LayerID_Actor, "Actors", agl::lyr::DisplayType_TopTV, nullptr)->setParentRenderer(&this->layerRenderer);
}

void Atlys::Renderer::init(Atlys::Camera* camera) {
    for (u32 i = 0; i < Atlys::Scene::instance()->map->info->layerCount; i++) {
        Atlys::Scene::instance()->map->layers[i].gtx.load(Atlys::Scene::instance()->map->layers[i].gtxName);
    }

    for (u32 i = 0; i < Atlys::Scene::instance()->map->info->animTexCount; i++) {
        Atlys::Scene::instance()->map->animTexs[i].init(Atlys::Scene::instance()->map->animTexs[i].gtxName);
    }
 
    ResMgr::instance()->loadRes("kanibo", "actor/kanibo.szs", nullptr, true);
    ResArchiveMgr::instance()->loadResArchive("kanibo", "kanibo", nullptr);
    for (u32 i = 0; i < Atlys::Scene::instance()->map->info->nodeCount; i++) {
        if (Atlys::Scene::instance()->map->nodes[i].type != Atlys::Map::Node::Type_Level)
            continue;
        
        Atlys::Scene::instance()->map->nodes[i].model = ModelWrapper::create("kanibo", "kanibo");
    }

    agl::lyr::Renderer::instance()->layers[Atlys::Renderer::LayerID_Map]->camera = &camera->camera;
    agl::lyr::Renderer::instance()->layers[Atlys::Renderer::LayerID_Map]->projection = &camera->projection;

    agl::lyr::Renderer::instance()->layers[Atlys::Renderer::LayerID_Actor]->camera = &camera->camera;
    agl::lyr::Renderer::instance()->layers[Atlys::Renderer::LayerID_Actor]->projection = &camera->projection;
}

void Atlys::Renderer::activate() {
    this->bindDrawMethods();
}

void Atlys::Renderer::bindDrawMethods() {
    BIND_DRAW_METHOD(drawMethodMap, "Map", &Atlys::Renderer::drawLayerMap, Atlys::Renderer::LayerID_Map);
    BIND_DRAW_METHOD(drawMethodActors, "Actors", &Atlys::Renderer::drawLayerActors, Atlys::Renderer::LayerID_Actor);
}

void Atlys::Renderer::drawLayerMap(const agl::lyr::RenderInfo& renderInfo) {
    Mtx44 viewProj;
    sead::Matrix44CalcCommon<f32>::multiply(viewProj, Atlys::Scene::instance()->camera->projection.getDeviceProjectionMatrix(), Atlys::Scene::instance()->camera->camera.matrix);

    for (u32 i = 0; i < Atlys::Scene::instance()->map->info->layerCount; i++) {
        Mtx34 quadMtxSRT;
        Mtx34::makeSRT(
            quadMtxSRT,
            Vec3f(Atlys::Scene::instance()->map->layers[i].size),
            Vec3f(degToRad(-90.0f), 0.0f, 0.0f),
            Vec3f(Atlys::Scene::instance()->map->layers[i].position.x, 0.0f, Atlys::Scene::instance()->map->layers[i].position.y)
        );

        agl::utl::DevTools::drawTextureTexCoord(
            Atlys::Scene::instance()->map->layers[i].gtx.texture,
            quadMtxSRT,
            viewProj
        );
    }

    for (u32 i = 0; i < Atlys::Scene::instance()->map->info->animTexCount; i++) {
        Mtx34 quadMtxSRT;
        Mtx34::makeSRT(
            quadMtxSRT,
            Vec3f(Atlys::Scene::instance()->map->animTexs[i].scale.x, Atlys::Scene::instance()->map->animTexs[i].scale.y, 1.0f),
            Vec3f(degToRad(-90.0f), degToRad(Atlys::Scene::instance()->map->animTexs[i].rotation), 0.0f),
            Vec3f(Atlys::Scene::instance()->map->animTexs[i].position.x, 0.0f, Atlys::Scene::instance()->map->animTexs[i].position.y)
        );

        agl::utl::DevTools::drawTextureTexCoord(
            Atlys::Scene::instance()->map->animTexs[i].gtx.texture,
            quadMtxSRT,
            viewProj
        );
    }
}

void Atlys::Renderer::drawLayerActors(const agl::lyr::RenderInfo& renderInfo) {
    DrawMgr::instance()->setTargetLayer(agl::lyr::Renderer::instance()->layers[Atlys::Renderer::LayerID_Actor], 1);

    ActorMgr::instance()->drawActors();

    // Draw nodes here too cause they are 3D models
    for (u32 i = 0; i < Atlys::Scene::instance()->map->info->nodeCount; i++) {
        Atlys::Scene::instance()->map->nodes[i].draw();
    }

    DrawMgr::instance()->resetTargetLayer();
}
