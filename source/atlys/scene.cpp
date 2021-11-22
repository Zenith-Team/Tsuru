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
    //! TODO: THIS BREAKS THE ENTIRE TASK, WTF HOW
    //this->map = new Map("tsuru/map.atlys");
    this->renderer.initRendering();

    // This has to go last
    this->adjustHeapAll();
}

void Atlys::Scene::enter() {
    LOG("Enter");

    // Make draw methods and bind to the corresponding layers
    this->renderer.makeDrawMethods();
}

void Atlys::Scene::calc() {
    ActorMgr::instance()->executeActors();
}

Atlys::Actor* Atlys::Scene::spawnSystemActor(ProfileID::ProfileIDType id) {
    ActorBuildInfo buildInfo = { 0 };
    buildInfo.profile = Profile::get(id);
    return (Atlys::Actor*) ActorMgr::instance()->create(buildInfo, 0);
}
