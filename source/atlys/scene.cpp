#include "tsuru/atlys.h"

#include "log.h"

// Game
#include "game/actor/actormgr.h"

// AGL
#include "agl/lyr/renderer.h"
#include "agl/lyr/renderinfo.h"

// SEAD
#include "sead/primitiverenderer.h"

SEAD_SINGLETON_TASK_IMPL(Atlys::Scene)

Atlys::Scene::Scene(const sead::TaskConstructArg& arg)
    : CalculateTask(arg, "AtlysScene")
    , drawMethodMap()
    , drawMethodActors()
    , controllers()
    , camera(nullptr)
    , renderer()
{ }

sead::TaskBase* Atlys::Scene::construct(const sead::TaskConstructArg& arg) {
    return new(arg.heapArray->heaps[arg.heapArray->primaryIndex], 4) Atlys::Scene(arg);
}

void Atlys::Scene::prepare() {
    LOG("Preparing Atlys...");

    // Initialize singletons
    ActorMgr::createInstance(nullptr)->createHeaps(nullptr);

    // Create layers
    agl::lyr::Renderer::instance()->createLayer<Atlys::Scene::RenderLayer>(LayerID_Map, "Map", 0, nullptr);
    agl::lyr::Renderer::instance()->createLayer<Atlys::Scene::RenderLayer>(LayerID_Actors, "Actors", 0, nullptr);

    this->adjustHeapAll();

    LOG("Done!");
}

void Atlys::Scene::enter() {
    LOG("Entering Atlys...");

    // Make draw methods and bind to corresponding layer
    MAKE_DRAW_METHOD(drawMethodMap, "Map", &Atlys::Scene::drawLayerMap, LayerID_Map);
    MAKE_DRAW_METHOD(drawMethodActors, "Actors", &Atlys::Scene::drawLayerActors, LayerID_Actors);

    ActorBuildInfo camBuildInfo = { 0 };
    camBuildInfo.profile = Profile::get(ProfileID::AtlysCamera);
    
    this->camera = (Atlys::Camera*) ActorMgr::instance()->create(camBuildInfo, 0);

    this->renderer.initShaders();

    LOG("Done!");
}

void Atlys::Scene::calc() {
    LOG("Atlys calc");
    ActorMgr::instance()->executeActors();
}

void Atlys::Scene::drawLayerMap(const agl::lyr::RenderInfo& renderInfo) {
    LOG("Drawing map layer");

    sead::PrimitiveRenderer::instance()->setCamera(this->camera->camera);
    sead::PrimitiveRenderer::instance()->setProjection(this->camera->projection);
    sead::PrimitiveRenderer::instance()->setModelMatrix(this->camera->camera.matrix);
    sead::PrimitiveRenderer::instance()->drawCube(Vec3f(-999.0f), 999999999999999999999999999999999.0f, sead::colorRed);
    sead::PrimitiveRenderer::instance()->end();

    LOG("Camera: %x, Display Type: %u, Layer: %x, Projection: %x, Render Buffer: %x", renderInfo.camera, renderInfo.displayType, renderInfo.layer, renderInfo.projection, renderInfo.renderBuffer);
}

void Atlys::Scene::drawLayerActors(const agl::lyr::RenderInfo& renderInfo) {
    LOG("Drawing actors layer");

    ActorMgr::instance()->drawActors();
}
