#include "tsuru/atlys.h"

#include "log.h"

// Game
#include "game/actor/actormgr.h"
#include "game/task/taskmgr.h"

// AGL
#include "agl/lyr/renderer.h"
#include "agl/lyr/renderinfo.h"

SEAD_SINGLETON_TASK_IMPL(Atlys::Scene)

Atlys::Scene::Scene(const sead::TaskConstructArg& arg)
    : CalculateTask(arg, "AtlysScene")
    , drawMethodMap()
    , drawMethodActors()
    , controllers()
    , camera(nullptr)
{ }

sead::TaskBase* Atlys::Scene::construct(const sead::TaskConstructArg& arg) {
    return new(arg.heapArray->heaps[arg.heapArray->primaryIndex], 4) Atlys::Scene(arg);
}

void Atlys::Scene::prepare() {
    LOG("Preparing Atlys...");

    // Initialize singletons
    ActorMgr::createInstance(nullptr)->createHeaps(nullptr);

    // Create layers
    // These are also required for levels because it will crash when it tries to access layers with these IDs, since it assumes CourseSelectTask made them
    agl::lyr::Renderer::instance()->createLayer<Atlys::Scene::RenderLayer>(LayerID_Map, "Map", 0, nullptr);
    agl::lyr::Renderer::instance()->createLayer<Atlys::Scene::RenderLayer>(LayerID_Actors, "Actors", 0, nullptr);

    // Init controller input
    this->controllers.init();

    this->adjustHeapAll();

    LOG("Done!");
}

void Atlys::Scene::enter() {
    LOG("Entering Atlys...");

    // Make draw methods and bind to corresponding layer
    MAKE_DRAW_METHOD(drawMethodMap, "Map", &Atlys::Scene::drawLayerMap, LayerID_Map);
    MAKE_DRAW_METHOD(drawMethodActors, "Actors", &Atlys::Scene::drawLayerActors, LayerID_Actors);

    ActorBuildInfo cameraBuildInfo = { 0 };
    ActorBuildInfo playerBuildInfo = { 0 };

    cameraBuildInfo.profile = Profile::get(ProfileID::AtlysCamera);
    playerBuildInfo.profile = Profile::get(ProfileID::AtlysPlayer);

    this->camera = (Atlys::Camera*) ActorMgr::instance()->create(cameraBuildInfo, 0);
    this->player = (Atlys::Player*) ActorMgr::instance()->create(playerBuildInfo, 0);

    LOG("Done!");
}

void Atlys::Scene::calc() {
    this->player->updateControllerInput(this->controllers);

    ActorMgr::instance()->executeActors();
}

void Atlys::Scene::drawLayerMap(const agl::lyr::RenderInfo& renderInfo) {
}

void Atlys::Scene::drawLayerActors(const agl::lyr::RenderInfo& renderInfo) {
    ActorMgr::instance()->drawActors();
}
