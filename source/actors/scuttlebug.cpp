#include "game/actor/stage/enemy.h"
#include "game/graphics/model/modelnw.h"
#include "game/graphics/drawmgr.h"

class Scuttlebug : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(Scuttlebug, Enemy);

public:
    Scuttlebug(const ActorBuildInfo* buildInfo);
    virtual ~Scuttlebug() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    void updateModel();

    static const HitboxCollider::Info collisionInfo;

    ModelWrapper* model;
    ModelWrapper* string;

    u32 timerIdleRaised, timerIdleLowered, timerLowering, timerRising;

    u16 dropDistance;
    u16 idleTime;

    DECLARE_STATE(Scuttlebug, OneTimeLowering);
    DECLARE_STATE(Scuttlebug, Lowering);
    DECLARE_STATE(Scuttlebug, IdleLowered);
    DECLARE_STATE(Scuttlebug, Rising);
    DECLARE_STATE(Scuttlebug, IdleRaised);
    DECLARE_STATE(Scuttlebug, Die);
};

CREATE_STATE(Scuttlebug, OneTimeLowering);
CREATE_STATE(Scuttlebug, Lowering);
CREATE_STATE(Scuttlebug, IdleLowered);
CREATE_STATE(Scuttlebug, Rising);
CREATE_STATE(Scuttlebug, IdleRaised);
CREATE_STATE(Scuttlebug, Die);

const ActorInfo ScuttlebugActorInfo = {
    Vec2i(8, -16), Vec2i(0, 16), Vec2i(8, 16), 0, 0, 0, 0, 0
};

const HitboxCollider::Info Scuttlebug::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(16.0f, 16.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0x20208, 0, &Enemy::collisionCallback
};

const Profile ScuttlebugProfile(&Scuttlebug::build, ProfileID::Scuttlebug, "Scuttlebug", &ScuttlebugActorInfo);
PROFILE_RESOURCES(ProfileID::Scuttlebug, Profile::LoadResourcesAt::Course, "gasagoso");

Scuttlebug::Scuttlebug(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , string(nullptr)
    , timerIdleRaised(0)
    , timerIdleLowered(0)
    , timerLowering(0)
    , timerRising(0)
    , dropDistance(0)
    , idleTime(150)
{ }

Actor* Scuttlebug::build(const ActorBuildInfo* buildInfo) {
    return new Scuttlebug(buildInfo);
}

u32 Scuttlebug::onCreate() {
    this->rotation.x += 0x800000 * 100;

    this->model = ModelWrapper::create("gasagoso", "gasagoso", 4);
    this->string = ModelWrapper::create("gasagoso", "string");

    this->hitboxCollider.init(this, &Scuttlebug::collisionInfo);
    this->addHitboxColliders();

    this->dropDistance = ((this->eventID1 >> 0x4 & 0xF) + 1) * 100; // Nybble 1

    this->updateModel();

    this->doStateChange(&Scuttlebug::StateID_OneTimeLowering);

    return 1;
}

u32 Scuttlebug::onExecute() {
    this->handleGravity();
    this->handleSpeed();

    if (this->timerLowering >= 200) {
        this->speed.y = 0.0f;
    } else {
        this->timerLowering++;
    }

    this->states.execute();

    this->updateModel();

    return 1;
}

u32 Scuttlebug::onDraw() {
    this->model->draw();
    this->string->draw();

    return 1;
}

void Scuttlebug::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    u32 hitType = this->processCollision(hcSelf, hcOther);

    if (hitType == 0)
        this->damagePlayer(hcSelf, hcOther);
    else
        this->killPlayerJump(hcOther->owner, 0.0f, &Scuttlebug::StateID_Die);
}

bool Scuttlebug::collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->isDeleted = true;

    return true;
}

bool Scuttlebug::collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->isDeleted = true;

    return true;
}

void Scuttlebug::updateModel() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);

    this->model->setMtx(mtx);
    this->string->setMtx(mtx);
    this->model->setScale(this->scale * 2.5);
    this->string->setScale(this->scale * 2.5);
    this->model->updateModel();
    this->string->updateModel();
    this->model->updateAnimations();
}

/** STATE: OneTimeLowering */

void Scuttlebug::beginState_OneTimeLowering() {
    this->model->playSklAnim("walk");
    this->timerLowering = 0;
    this->gravity = -0.1875f;
    this->maxSpeed.y = -4.0f;
}

void Scuttlebug::executeState_OneTimeLowering() {
    if (this->timerLowering >= this->dropDistance / 3) {
        this->speed.y = 0.0f;
        this->doStateChange(&Scuttlebug::StateID_IdleLowered);
    } else {
        this->timerLowering++;
    }
}

void Scuttlebug::endState_OneTimeLowering() { }

/** STATE: Lowering */

void Scuttlebug::beginState_Lowering() {
    this->timerLowering = 0;
    this->gravity = -0.0875f;
    this->maxSpeed.y = -1.0f;
}

void Scuttlebug::executeState_Lowering() {
    if (this->timerLowering >= this->dropDistance) {
        this->speed.y = 0.0f;
        this->doStateChange(&Scuttlebug::StateID_IdleLowered);
    } else {
        this->timerLowering++;
    }
}

void Scuttlebug::endState_Lowering() { }

/** STATE: IdleLowered */

void Scuttlebug::beginState_IdleLowered() {
    this->timerIdleLowered = 0;
}

void Scuttlebug::executeState_IdleLowered() {
    if (this->timerIdleLowered >= idleTime) {
        this->doStateChange(&Scuttlebug::StateID_Rising);
    } else {
        this->timerIdleLowered++;
    }
}

void Scuttlebug::endState_IdleLowered() { }

/** STATE: Rising */

void Scuttlebug::beginState_Rising() {
    this->timerRising = 0;
    this->gravity = 0.0875f;
    this->maxSpeed.y = 1.0f;
}

void Scuttlebug::executeState_Rising() {
    u16 riseDistance = dropDistance / 2;
    riseDistance -= 5; // Bugfix for it slowly rising

    if (this->timerRising >= riseDistance) {
        this->speed.y = 0.0f;
        this->doStateChange(&Scuttlebug::StateID_IdleRaised);
    } else {
        this->timerRising++;
    }
}

void Scuttlebug::endState_Rising() { }

/** STATE: IdleRaised */

void Scuttlebug::beginState_IdleRaised() {
    this->timerIdleRaised = 0;
    this->gravity = 0.0f;
    this->maxSpeed.y = 0.0f;
}

void Scuttlebug::executeState_IdleRaised() {
    if (this->timerIdleRaised >= idleTime) {
        this->doStateChange(&Scuttlebug::StateID_Lowering);
    } else {
        this->timerIdleRaised++;
    }
}

void Scuttlebug::endState_IdleRaised() { }

/** STATE: Die */

void Scuttlebug::beginState_Die() {
    this->gravity = -0.2875f;
    this->maxSpeed.y = -14.0f;

    this->removeHitboxColliders();
}

void Scuttlebug::executeState_Die() {
    this->isDeleted = true;
}

void Scuttlebug::endState_Die() { }
