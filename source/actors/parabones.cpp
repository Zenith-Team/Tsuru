#include <game/actor/stage/enemy.h>
#include <game/actor/actormgr.h>
#include <game/direction.h>
#include <game/graphics/drawmgr.h>

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

    void modelUpdate();

    ModelWrapper* model;
    u32 timerIdleLowered;
    u32 timerIdleRaised;
    u32 timerLowering;
    u32 timerRising;
    u16 flyDistance;
    u16 idleTime;

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
const Profile ParaBonesProfile(&ParaBones::build, ProfileID::ParaBones, "ParaBones", &ParaBonesActorInfo, 0);
PROFILE_RESOURCES(ProfileID::ParaBones, "nokonokoB");

const HitboxCollider::Info ParaBones::sCollisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(16.0f, 16.0f), HitboxCollider::ShapeRectangle, 3, 0, 0xFFFFFFFF, 0xFFFFFFFF, 0, &Enemy::collisionCallback
};

ParaBones::ParaBones(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
{ }

Actor* ParaBones::build(const ActorBuildInfo* buildInfo) {
    return new ParaBones(buildInfo);
}

u32 ParaBones::onCreate() {
    Vec3u rotationOffset(0, 1000, 0);
    this->rotation.y = Direction::directionToRotationList[Direction::Left];

    model = ModelWrapper::create("nokonokoB", "nokonokoB", 10);
    model->playSklAnim("flyA", 0);

    hitboxCollider.init(this, &ParaBones::sCollisionInfo, nullptr);
    addHitboxColliders();

    flyDistance = 200;
    idleTime = 150;

    doStateChange(&ParaBones::StateID_Lowering);

    modelUpdate();

    return 1;
}

u32 ParaBones::onExecute() {
    handleGravity();
    handleSpeed();

    if (timerLowering >= flyDistance)
        speed.y = 0.0f;
    else
        timerLowering += 1;

    states.execute();

    modelUpdate();

    return 1; 
}

u32 ParaBones::onDraw() {
    DrawMgr::instance()->drawModel(model);

    return 1;
}

void ParaBones::modelUpdate() {
    Mtx34 mtx;

    mtx.rotateAndTranslate(rotation, position);

    model->setMtx(mtx);
    model->setScale(scale);
    model->updateModel();
    model->updateAnimations();
}

void ParaBones::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    u32 hitType = processCollision(hcSelf, hcOther, 0);

    if (hitType == 0)
        damagePlayer(hcSelf, hcOther);
    else if (hitType == 1 || hitType == 3)
        killPlayerJump(hcOther->owner, 0.0f, &ParaBones::StateID_Die);
}

// Lowering state

void ParaBones::beginState_Lowering() {
    timerLowering = 0;
    gravity = -1.0f;
    maxSpeed.y = -1.0f;
}

void ParaBones::executeState_Lowering() {
    if (timerLowering >= flyDistance) {
        speed.y = 0.0f;
        doStateChange(&ParaBones::StateID_IdleLowered);
    }

    else
        timerLowering++;
}

void ParaBones::endState_Lowering() { }


// IdleLowered state

void ParaBones::beginState_IdleLowered() {
    timerIdleLowered = 0;
    gravity = 0.0f;
    maxSpeed.y = 0.0f;
}

void ParaBones::executeState_IdleLowered() {
    if (timerIdleLowered >= idleTime)
        doStateChange(&ParaBones::StateID_Rising);
    else
        timerIdleLowered++;
}

void ParaBones::endState_IdleLowered() { }


// Rising state

void ParaBones::beginState_Rising() {
    timerRising = 0;
    gravity = 0.0875f;
    maxSpeed.y = 1.0f;
}

void ParaBones::executeState_Rising() {
    if (timerRising >= flyDistance / 2) {
        speed.y = 0.0f;
        doStateChange(&ParaBones::StateID_IdleRaised);
    }

    else
        timerRising++;
}

void ParaBones::endState_Rising() { }


// IdleRaised state

void ParaBones::beginState_IdleRaised() {
    timerIdleRaised = 0;
    gravity = 0.0f;
    maxSpeed.y = 0.0f;
}

void ParaBones::executeState_IdleRaised() {
    if (timerIdleRaised >= idleTime)
        doStateChange(&ParaBones::StateID_Lowering);
    else
        timerIdleRaised++;
}

void ParaBones::endState_IdleRaised() { }


// Die state

void ParaBones::beginState_Die() {
    removeHitboxColliders();
    Vec3f posKillFix(0.0f, -8.0f, 0.0f);

    ActorBuildInfo DryBones = { 0 };
    DryBones.profile = Profile::get(Profile::spriteToProfileList[137]);
    DryBones.position += posKillFix;
    ActorMgr::instance()->create(&DryBones, 0);
    this->isDeleted = true;
}

void ParaBones::executeState_Die() { }

void ParaBones::endState_Die() { }
