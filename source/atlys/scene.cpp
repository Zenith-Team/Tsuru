#include "tsuru/atlys/scene.h"
#include "game/actor/actormgr.h"
#include "game/profile/profile.h"
#include "log.h"
#include "game/resource/resarchive.h"
#include "game/resource/resmgr.h"

SEAD_SINGLETON_TASK_IMPL(Atlys::Scene)

CREATE_STATE(Atlys::Scene, Active);
CREATE_STATE(Atlys::Scene, Paused);

Atlys::Scene::Scene(const sead::TaskConstructArg& arg)
    : CalculateTask(arg, "AtlysScene")
    , states(this)
    , renderer()
    , controllers()
    , activeController(InputControllers::ControllerID_Gamepad)
    , map(nullptr)
    , player(nullptr)
    , camera(nullptr)
{ }

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

    // Load the resources for profiles
    Profile::loadProfileResources(Profile::LoadResourcesAt_CourseSelect, nullptr);

    // Spawn system actors
    this->player = (Atlys::Player*) Scene::spawnSystemActor(ProfileID::AtlysPlayer);
    this->camera = (Atlys::Camera*) Scene::spawnSystemActor(ProfileID::AtlysCamera);

    // Init the renderer
    this->renderer.init(this->camera);

    //! This has to go last!
    //this->adjustHeapAll();

    //* Cannot allocate anything else to the task heap from this point on...
}

void Atlys::Scene::enter() {
    // Activate renderer
    // It will be automatically managed from now on
    this->renderer.activate();

    this->states.changeState(&Atlys::Scene::StateID_Active);
}

void Atlys::Scene::calc() {
    this->states.execute();
}

Atlys::Actor* Atlys::Scene::spawnSystemActor(ProfileID::ProfileIDType id, Vec3f position) {
    ActorBuildInfo buildInfo = { 0 };
    buildInfo.profile = Profile::get(id);
    buildInfo.position = position;
    return (Atlys::Actor*) ActorMgr::instance()->create(buildInfo, 0);
}

/* STATE: Active */

void Atlys::Scene::beginState_Active() { }

void Atlys::Scene::executeState_Active() {
    ActorMgr::instance()->executeActors();

    if (this->controllers.buttonPlus(this->activeController)) {
        LOG("Pausing");
        this->states.changeState(&Atlys::Scene::StateID_Paused);
    }
}

void Atlys::Scene::endState_Active() { }

/* STATE: Paused */

void Atlys::Scene::beginState_Paused() { }

void Atlys::Scene::executeState_Paused() {
    if (this->controllers.buttonA(this->activeController)) {
        LOG("Unpausing");
        this->states.changeState(&Atlys::Scene::StateID_Active);
    }
}

void Atlys::Scene::endState_Paused() { }
