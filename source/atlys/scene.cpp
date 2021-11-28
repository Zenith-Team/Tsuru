#include "tsuru/atlys/scene.h"
#include "game/actor/actormgr.h"
#include "log.h"

SEAD_SINGLETON_TASK_IMPL(Atlys::Scene)

Atlys::Scene::Scene(const sead::TaskConstructArg& arg)
    : CalculateTask(arg, "AtlysScene")
    , renderer()
    , controllers()
    , map(nullptr)
{ }

Atlys::Scene::~Scene() {
    delete this->map; this->map = nullptr;
}

sead::TaskBase* Atlys::Scene::construct(const sead::TaskConstructArg& arg) {
    return new(arg.heapArray->heaps[arg.heapArray->primaryIndex], 4) Atlys::Scene(arg);
}

void Atlys::Scene::prepare() {
    LOG("Preparing");

    // Initialize singletons
    ActorMgr::createInstance(nullptr)->createHeaps(nullptr);

    // Create render layers
    this->renderer.makeLayers();

    // Initialize controller input
    this->controllers.init();

    // Load map file
    this->map = new Map("tsuru/map.atlys");
    
    this->renderer.loadMapTextures();

    // This has to go last
    this->adjustHeapAll();
}

void Atlys::Scene::enter() {
    LOG("Enter");

    // Init renderer
    // It will be automatically managed from now on
    this->renderer.init();
}

void Atlys::Scene::calc() {
    ActorMgr::instance()->executeActors();
}

Atlys::Actor* Atlys::Scene::spawnSystemActor(ProfileID::ProfileIDType id) {
    ActorBuildInfo buildInfo = { 0 };
    buildInfo.profile = Profile::get(id);
    return (Atlys::Actor*) ActorMgr::instance()->create(buildInfo, 0);
}
