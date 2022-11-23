#include "game/actor/stage/enemy.h"
#include "game/graphics/model/modelnw.h"
#include "game/graphics/drawmgr.h"
#include "game/effect/effect.h"

class Scuttlebug : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(Scuttlebug, Enemy);

public:
    Scuttlebug(const ActorBuildInfo* buildInfo);
    virtual ~Scuttlebug() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    void collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionPenguinSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionGroundPoundYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionPropellerDrill(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionFireballYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    static const HitboxCollider::Info collisionInfo;

    ModelWrapper* model;
    ModelWrapper* string;
    u32 timerIdleLowered;
    u32 timerIdleRaised;
    u32 timerLowering;
    u32 timerRising;
    u16 moveDistance;
    u16 idleTime;

    DECLARE_STATE(Scuttlebug, Lowering);
    DECLARE_STATE(Scuttlebug, IdleLowered);
    DECLARE_STATE(Scuttlebug, Rising);
    DECLARE_STATE(Scuttlebug, IdleRaised);
    DECLARE_STATE(Scuttlebug, Die);
};

CREATE_STATE(Scuttlebug, Lowering);
CREATE_STATE(Scuttlebug, IdleLowered);
CREATE_STATE(Scuttlebug, Rising);
CREATE_STATE(Scuttlebug, IdleRaised);
CREATE_STATE(Scuttlebug, Die);

REGISTER_PROFILE(Scuttlebug, ProfileID::Scuttlebug);
PROFILE_RESOURCES(ProfileID::Scuttlebug, Profile::LoadResourcesAt::Course, "gasagoso");

const HitboxCollider::Info Scuttlebug::collisionInfo = {
    Vec2f(0.0f, -4.0f), Vec2f(16.0f, 16.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0xFFFFFFFF, 0xFFFBFFFF, 0, &Enemy::collisionCallback
};

Scuttlebug::Scuttlebug(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
{ }

u32 Scuttlebug::onCreate() {
    this->rotation = Vec3u(fixDeg(90.0f), 0, 0);

    this->hitboxCollider.init(this, &collisionInfo);
    this->addHitboxColliders();

    // 30 = 1 tile
    this->moveDistance = 30 * (this->settings1 >> 0x1C & 0xF); // nybble 5
    // 30 = 0.5 seconds
    this->idleTime = 30 * (this->settings1 >> 0x18 & 0xF); // nybble 6

    this->speed.y = 0.0f;
    this->gravity = 0.0f;
    this->maxSpeed.y = 0.0f;

    this->model = ModelWrapper::create("gasagoso", "gasagoso", 1);
    this->string = ModelWrapper::create("gasagoso", "string");

    this->model->playSklAnim("walk");

    return this->onExecute();
}

u32 Scuttlebug::onExecute() {
    Mtx34 mtx;

    mtx.makeRTIdx(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->setScale(this->scale * 2.5f);
    this->model->updateModel();
    this->model->updateAnimations();

    mtx.makeRTIdx(this->rotation, this->position);
    this->string->setMtx(mtx);
    this->string->setScale(this->scale * 2.5f);
    this->string->updateModel();

    this->handlePhysics();

    return 1;
}

u32 Scuttlebug::onDraw() {
    this->model->draw();
    this->string->draw();

    return 1;
}

void Scuttlebug::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    u32 hitType = this->processCollision(hcSelf, hcOther, 0);

    if (hitType == Enemy::HitType::Collide) {
        this->damagePlayer(hcSelf, hcOther);
    } else if (hitType == Enemy::HitType::NormalJump || hitType == Enemy::HitType::SpinJump) {
        this->killPlayerJump(hcOther->owner, 0.0f, &Scuttlebug::StateID_Die);
    }
}

void Scuttlebug::collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    u32 hitType = this->processCollision(hcSelf, hcOther, 0);

    if (hitType == Enemy::HitType::Collide) {
        this->damagePlayer(hcSelf, hcOther);
    } else if (hitType == Enemy::HitType::NormalJump || hitType == Enemy::HitType::SpinJump) {
        this->killPlayerJump(hcOther->owner, 0.0f, &Scuttlebug::StateID_Die);
        Vec3f effectOrigin(this->position.x, this->position.y, 4500.0f);
        Vec3f effectPos(effectOrigin);
        Effect::spawn(RP_Jugemu_CloudDisapp, &effectPos, nullptr, &this->scale);
    }
}

bool Scuttlebug::collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return this->collisionStar(hcSelf, hcOther);
}

bool Scuttlebug::collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    Vec3f effectOrigin(this->position.x, this->position.y, 4500.0f);
    Vec3f effectPos(effectOrigin);
    Effect::spawn(RP_Jugemu_CloudDisapp, &effectPos, nullptr, &this->scale);

    this->isDeleted = true;

    return true;
}

bool Scuttlebug::collisionSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return this->collisionStar(hcSelf, hcOther);
}

bool Scuttlebug::collisionPenguinSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return this->collisionStar(hcSelf, hcOther);
}

bool Scuttlebug::collisionGroundPoundYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return this->collisionStar(hcSelf, hcOther);
}

bool Scuttlebug::collisionPropellerDrill(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return this->collisionStar(hcSelf, hcOther);
}

bool Scuttlebug::collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return this->collisionStar(hcSelf, hcOther);
}

bool Scuttlebug::collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return this->collisionStar(hcSelf, hcOther);
}

bool Scuttlebug::collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return this->collisionStar(hcSelf, hcOther);
}

bool Scuttlebug::collisionFireballYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return this->collisionFireball(hcSelf, hcOther);
}

/** STATE: Lowering */

void Scuttlebug::beginState_Lowering() {
    this->timerLowering = 0;
    this->gravity = -1.0f;
    this->maxSpeed.y = -1.0f;
}

void Scuttlebug::executeState_Lowering() {
    if (this->timerLowering >= this->moveDistance / 2) {
        this->speed.y = 0.0f;
        this->doStateChange(&Scuttlebug::StateID_IdleLowered);
    }
    else this->timerLowering++;
}

void Scuttlebug::endState_Lowering() { }

/** STATE: IdleLowered */

void Scuttlebug::beginState_IdleLowered() {
    this->timerIdleLowered = 0;
    this->gravity = 0.0f;
    this->maxSpeed.y = 0.0f;
}

void Scuttlebug::executeState_IdleLowered() {
    if (this->timerIdleLowered >= this->idleTime)
        this->doStateChange(&Scuttlebug::StateID_Rising);
    else
        this->timerIdleLowered++;
}

void Scuttlebug::endState_IdleLowered() { }

/** STATE: Rising */

void Scuttlebug::beginState_Rising() {
    this->timerRising = 0;
    this->gravity = 0.0875f;
    this->maxSpeed.y = 1.0f;
}

void Scuttlebug::executeState_Rising() {
    if (this->timerRising >= this->moveDistance / 2) {
        this->speed.y = 0.0f;
        this->doStateChange(&Scuttlebug::StateID_IdleRaised);
    }
    else this->timerRising++;
}

void Scuttlebug::endState_Rising() { }

/** STATE: IdleRaised */

void Scuttlebug::beginState_IdleRaised() {
    this->timerIdleRaised = 0;
    this->gravity = 0.0f;
    this->maxSpeed.y = 0.0f;
}

void Scuttlebug::executeState_IdleRaised() {
    if (this->timerIdleRaised >= this->idleTime)
        this->doStateChange(&Scuttlebug::StateID_Lowering);
    else
        this->timerIdleRaised++;
}

void Scuttlebug::endState_IdleRaised() { }

/** STATE: Die */

void Scuttlebug::beginState_Die() {
    this->removeHitboxColliders();
    this->isDeleted = true;
}

void Scuttlebug::executeState_Die() { }

void Scuttlebug::endState_Die() { }
