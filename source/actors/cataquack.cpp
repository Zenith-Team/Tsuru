#include "game/actor/stage/enemy.h"
#include "game/actor/actormgr.h"
#include "game/direction.h"
#include "game/graphics/drawmgr.h"
#include "game/util.h"
#include "log.h"
#include "tsuru/utils.h"

class Cataquack : public Enemy {
public:
    Cataquack(const ActorBuildInfo* buildInfo);
    virtual ~Cataquack() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void updateModel();

    ModelWrapper* model;

    DECLARE_STATE(Cataquack, IdleWalking);
    DECLARE_STATE(Cataquack, Turn);
};
CREATE_STATE(Cataquack, IdleWalking);
CREATE_STATE(Cataquack, Turn);

const ActorInfo CataquackActorInfo = {
    Vec2i(8, -8), Vec2i(8, -8), Vec2i(32, 32), 0, 0, 0, 0, 0
};
const Profile CataquackProfile(&Cataquack::build, ProfileID::Cataquack, "Cataquack", &CataquackActorInfo, Profile::Flag_DontRenderOffScreen);
PROFILE_RESOURCES(ProfileID::Cataquack, "poihana");

Cataquack::Cataquack(const ActorBuildInfo* buildInfo) : Enemy(buildInfo) { };

Actor* Cataquack::build(const ActorBuildInfo* buildInfo) {
    return new Cataquack(buildInfo);
}

u32 Cataquack::onCreate() {
    this->model = ModelWrapper::create("poihana", "poihana", 3);
    this->scale.x = 0.1f;
    this->scale.y = 0.1f;
    this->scale.z = 0.1f;
    this->model->playSklAnim("walk", 0);

    PhysicsMgr::Sensor belowSensor = { -6,  6,  0 };
    PhysicsMgr::Sensor aboveSensor = { -6,  6, 28 };
    PhysicsMgr::Sensor sidesSensor = {  4, 20, 12 };
    this->physicsMgr.init(this, &belowSensor, &aboveSensor, &sidesSensor);

    this->direction = this->directionToPlayerH(this->position);

    doStateChange(&Cataquack::StateID_IdleWalking);
    this->updateModel();
    return 1;
}

u32 Cataquack::onExecute() {
    this->states.execute();
    this->updateModel();
    return 1;
}

u32 Cataquack::onDraw() {
    DrawMgr::instance()->drawModel(this->model);
    return 1;
}

void Cataquack::updateModel() {
    Mtx34 mtx;
    mtx.rotateAndTranslate(this->rotation, this->position + Vec3f(0.0f, 20.0f, 0.0f));
    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateAnimations();
    this->model->updateModel();
}

/* STATE: IdleWalking */

void Cataquack::beginState_IdleWalking() {
    this->speed.x    = this->direction == Direction::Left ? -0.5f : 0.5f;
    this->maxSpeed.x = this->direction == Direction::Left ? -0.5f : 0.5f;
}

void Cataquack::executeState_IdleWalking() {
    this->handleGravity();
    this->handleSpeed();
    this->physicsMgr.processCollisions();

    if (this->physicsMgr.isOnGround()) this->speed.y = 0.0f;
    if (this->physicsMgr.isCollided(this->direction)) doStateChange(&Cataquack::StateID_Turn);
}

void Cataquack::endState_IdleWalking() {}

/* STATE: Turn */

void Cataquack::beginState_Turn() {
    this->direction ^= 1;
    this->speed.x    = 0.0f;
    this->maxSpeed.x = 0.0f;
}

void Cataquack::executeState_Turn() {
    if (moveValueWithOverflowTo(this->rotation.y, Direction::directionToRotationList[this->direction], 0x2000000, this->direction)) {
        doStateChange(&this->StateID_IdleWalking);
    }
}

void Cataquack::endState_Turn() {
    this->rotation.y = Direction::directionToRotationList[this->direction];
}
