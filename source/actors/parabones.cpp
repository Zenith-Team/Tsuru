#include "game/actor/stage/enemy.h"
#include "game/actor/actormgr.h"
#include "game/direction.h"
#include "game/graphics/model/modelnw.h"

class ParaBones : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(ParaBones, Enemy)

public:
    ParaBones(const ActorBuildInfo* buildInfo);
    virtual ~ParaBones() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    void updateModel();

    ModelWrapper* model;
    ModelWrapper* wings;
    u32 timerIdleLowered;
    u32 timerIdleRaised;
    u32 timerLowering;
    u32 timerRising;
    u16 flyDistance;
    u16 idleTime;
    bool startRising;
    bool horizontal;

    static const HitboxCollider::Info sCollisionInfo;

    DECLARE_STATE(ParaBones, Lowering);
    DECLARE_STATE(ParaBones, IdleLowered);
    DECLARE_STATE(ParaBones, Rising);
    DECLARE_STATE(ParaBones, IdleRaised);
    DECLARE_STATE(ParaBones, Die);
};

CREATE_STATE(ParaBones, Lowering);
CREATE_STATE(ParaBones, IdleLowered);
CREATE_STATE(ParaBones, Rising);
CREATE_STATE(ParaBones, IdleRaised);
CREATE_STATE(ParaBones, Die);

const ActorInfo ParaBonesActorInfo = { Vec2i(8, -16), Vec2i(0, 16), Vec2i(8, 16), 0, 0, 0, 0, 0 };
const Profile ParaBonesProfile(&ParaBones::build, ProfileID::ParaBones, "ParaBones", &ParaBonesActorInfo);
PROFILE_RESOURCES(ProfileID::ParaBones, Profile::LoadResourcesAt::Course, "nokonokoB", "karon", "wing");

const HitboxCollider::Info ParaBones::sCollisionInfo = {
    Vec2f(0.0f, 8.0f), Vec2f(8.0f, 12.0f), HitboxCollider::Shape::Rectangle, 3, 0, 0xFFFFFFFF, 0xFFFFFFFF, 0, &Enemy::collisionCallback
};

ParaBones::ParaBones(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , wings(nullptr)
    , timerIdleLowered(0)
    , timerIdleRaised(0)
    , timerLowering(0)
    , timerRising(0)
    , flyDistance(0)
    , idleTime(0)
    , startRising(this->settings1 >> 0x14 & 0xF) // nybble 7
    , horizontal(this->settings1 >> 0x10 & 0xF) // nybble 8
{ }

Actor* ParaBones::build(const ActorBuildInfo* buildInfo) {
    return new ParaBones(buildInfo);
}

u32 ParaBones::onCreate() {
    this->rotation.y = Direction::directionToRotationList[Direction::Left] + 1000;

    this->model = ModelWrapper::create("nokonokoB", "nokonokoB", 10);
    this->model->playSklAnim("flyA", 0);

    this->wings = ModelWrapper::create("wing", "wing", 10);
    this->wings->playSklAnim("wing_kuri", 0); // wing_pata

    this->hitboxCollider.init(this, &ParaBones::sCollisionInfo, nullptr);
    this->addHitboxColliders();

    // 30 = 1 tile
    this->flyDistance = 30 * (this->settings1 >> 0x1C & 0xF); // nybble 5
    // 30 = 0.5 seconds
    this->idleTime = 30 * (this->settings1 >> 0x18 & 0xF); // nybble 6

    this->speed.y = 0.0f;
    this->gravity = 0.0f;
    this->maxSpeed.y = 0.0f;

    if (this->flyDistance != 0) {
        this->doStateChange(this->startRising ? &ParaBones::StateID_Rising : &ParaBones::StateID_Lowering);
    }

    this->updateModel();
    return 1;
}

u32 ParaBones::onExecute() {
    this->handleGravity();
    this->handleSpeed();

    if (this->startRising) {
        if (this->timerRising >= this->flyDistance)
            this->speed.y = 0.0f;
        else
            this->timerRising += 1;
    } else {
        if (this->timerLowering >= this->flyDistance)
            this->speed.y = 0.0f;
        else
            this->timerLowering += 1;
    }

    this->states.execute();
    this->updateModel();

    return 1;
}

u32 ParaBones::onDraw() {
    this->model->draw();
    this->wings->draw();
    return 1;
}

void ParaBones::updateModel() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateModel();
    this->model->updateAnimations();

    Mtx34 mtxWings;
    mtxWings.makeRTIdx(this->rotation, this->position + Vec3f(0.0f, 8.0f, 0.0f));
    this->wings->setMtx(mtxWings);
    this->wings->setScale(this->scale);
    this->wings->updateModel();
    this->wings->updateAnimations();
}

void ParaBones::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    u32 hitType = this->processCollision(hcSelf, hcOther, 0);

    if (hitType == 0)
        this->damagePlayer(hcSelf, hcOther);
    else if (hitType == 1 || hitType == 3)
        this->killPlayerJump(hcOther->owner, 0.0f, &ParaBones::StateID_Die);
}

// Lowering state

void ParaBones::beginState_Lowering() {
    this->timerLowering = 0;
    this->gravity = -1.0f;
    this->maxSpeed.y = -1.0f;
}

void ParaBones::executeState_Lowering() {
    if (this->timerLowering >= this->flyDistance / (this->startRising + 1)) {
        this->speed.y = 0.0f;
        this->doStateChange(&ParaBones::StateID_IdleLowered);
    }
    else this->timerLowering++;
}

void ParaBones::endState_Lowering() { }

// IdleLowered state

void ParaBones::beginState_IdleLowered() {
    this->timerIdleLowered = 0;
    this->gravity = 0.0f;
    this->maxSpeed.y = 0.0f;
}

void ParaBones::executeState_IdleLowered() {
    if (this->timerIdleLowered >= this->idleTime)
        this->doStateChange(&ParaBones::StateID_Rising);
    else
        this->timerIdleLowered++;
}

void ParaBones::endState_IdleLowered() { }

// Rising state

void ParaBones::beginState_Rising() {
    this->timerRising = 0;
    this->gravity = 0.0875f;
    this->maxSpeed.y = 1.0f;
}

void ParaBones::executeState_Rising() {
    if (this->timerRising >= this->flyDistance / (!this->startRising + 1)) {
        this->speed.y = 0.0f;
        this->doStateChange(&ParaBones::StateID_IdleRaised);
    }
    else this->timerRising++;
}

void ParaBones::endState_Rising() { }

// IdleRaised state

void ParaBones::beginState_IdleRaised() {
    this->timerIdleRaised = 0;
    this->gravity = 0.0f;
    this->maxSpeed.y = 0.0f;
}

void ParaBones::executeState_IdleRaised() {
    if (this->timerIdleRaised >= this->idleTime)
        this->doStateChange(&ParaBones::StateID_Lowering);
    else
        this->timerIdleRaised++;
}

void ParaBones::endState_IdleRaised() { }

// Die state

void ParaBones::beginState_Die() {
    this->removeHitboxColliders();

    ActorBuildInfo DryBones = { 0 };
    DryBones.profile = Profile::get(Profile::spriteToProfileList[137]);
    DryBones.position = this->position + Vec3f(0.0f, -8.0f, 0.0f);
    ActorMgr::instance()->create(DryBones, 0);
    this->isDeleted = true;
}

void ParaBones::executeState_Die() { }

void ParaBones::endState_Die() { }
