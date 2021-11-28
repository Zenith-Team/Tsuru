#include "tsuru/atlys/scene.h"
#include "game/actor/actormgr.h"
#include "log.h"

SEAD_SINGLETON_TASK_IMPL(Atlys::Scene)

Atlys::Scene::Scene(const sead::TaskConstructArg& arg)
    : CalculateTask(arg, "AtlysScene")
    , renderer()
    , controllers()
    , map(nullptr)
{
    this->setInstance(this);
}

Atlys::Scene::~Scene() {
    delete this->map; this->map = nullptr;
}

sead::TaskBase* Atlys::Scene::construct(const sead::TaskConstructArg& arg) {
    return new(arg.heapArray->heaps[arg.heapArray->primaryIndex], 4) Atlys::Scene(arg);
}

void Atlys::Scene::prepare() {
    // Initialize singletons
    ActorMgr::createInstance(nullptr)->createHeaps(nullptr);

    // Create render layers
    this->renderer.makeLayers();

    // Initialize controller input
    this->controllers.init();

    // Load map file
    this->map = new Map("tsuru/map.atlys");

    // Init the renderer
    this->renderer.init();

    // This has to go last!
    this->adjustHeapAll();

    // Cannot allocate anything else to the task heap from this point on...
}

void Atlys::Scene::enter() {
    // Activate renderer
    // It will be managed by the game from now on
    this->renderer.activate();
}

void Atlys::Scene::calc() {
    ActorMgr::instance()->executeActors();
}

Atlys::Actor* Atlys::Scene::spawnSystemActor(ProfileID::ProfileIDType id) {
    ActorBuildInfo buildInfo = { 0 };
    buildInfo.profile = Profile::get(id);
    return (Atlys::Actor*) ActorMgr::instance()->create(buildInfo, 0);
}
