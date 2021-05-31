#include "actor/enemy.h"

#include "drawmgr.h"
#include "actormgr.h"

class FlyBones : public Enemy {
public:
    FlyBones(const ActorBuildInfo* buildInfo);
    virtual ~FlyBones() { }

    static BaseActor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void collisionPlayer(HitboxCollider* acSelf, HitboxCollider* acOther) override;

    void updateModel();

    ModelWrapper* model;

    u32 timerIdleLowered;
    u32 timerIdleRaised;
    u32 timerLowering;
    u32 timerRising;

    u16 flyDistance;
    u16 idleTime;

    static const HitboxCollider::Info collisionInfo;

    DECLARE_STATE(FlyBones, Lowering)
    DECLARE_STATE(FlyBones, IdleLowered)
    DECLARE_STATE(FlyBones, Rising)
    DECLARE_STATE(FlyBones, IdleRaised)
    DECLARE_STATE(FlyBones, Die)
};

CREATE_STATE(FlyBones, Lowering);
CREATE_STATE(FlyBones, IdleLowered);
CREATE_STATE(FlyBones, Rising);
CREATE_STATE(FlyBones, IdleRaised);
CREATE_STATE(FlyBones, Die);

const ActorInfo FlyBonesActorInfo = { Vec2i(8, -16), Vec2i(0, 16), Vec2i(8, 16), 0, 0, 0, 0, 0 };
const Profile FlyBonesProfile(&FlyBones::build, ProfileId::Sprite310, "FlyBones", &FlyBonesActorInfo, 0);
PROFILE_RESOURCES(ProfileId::Sprite310, "nokonokoB");

const HitboxCollider::Info FlyBones::collisionInfo = { Vec2(0.0f, 0.0f), Vec2(16.0f, 16.0f), 1, 3, 0, 0xFFFFFFFF, 0xFFFFFFFF, 0, &Enemy::collisionCallback };

FlyBones::FlyBones(const ActorBuildInfo* buildInfo) : Enemy(buildInfo) { }

BaseActor* FlyBones::build(const ActorBuildInfo* buildInfo) {
    return new FlyBones(buildInfo);
}

u32 FlyBones::onCreate() {
    Vec3u rotationOffset(0, 1000, 0);
    this->rotation.y = directionToRotationList[Direction::Left];

    model = ModelWrapper::create("nokonokoB", "nokonokoB", 10);
    model->playSklAnim("flyA", 0);

    aCollider.init(this, &FlyBones::collisionInfo, nullptr);
    addHitboxColliders();

    flyDistance = 200;
    idleTime = 150;

    doStateChange(&FlyBones::StateID_Lowering);

    updateModel();

    return 1;
}

u32 FlyBones::onExecute() {
    handleGravity();
    handleSpeed();

    if (timerLowering >= flyDistance)
        speed.y = 0.0f;
    else
        timerLowering += 1;

    states.execute();

    updateModel();

    return 1;
}

u32 FlyBones::onDraw() {
    DrawMgr::instance->drawModel(model);

    return 1;
}

void FlyBones::updateModel() {
    Mtx34 mtx;

    mtx.rotateAndTranslate(rotation, position);

    model->setMtx(mtx);
    model->setScale(scale);
    model->updateModel();
    model->updateAnimations();
}

void FlyBones::collisionPlayer(HitboxCollider* acSelf, HitboxCollider* acOther) {
    u32 hitType = processCollision(acSelf, acOther, 0);

    if (hitType == 0)
        damagePlayer(acSelf, acOther);
    else if (hitType == 1 || hitType == 3)
        killPlayerJump(acOther->owner, 0.0f, &FlyBones::StateID_Die);
}

//* Lowering state

void FlyBones::beginState_Lowering() {
    timerLowering = 0;
    gravity = -1.0f;
    maxSpeed.y = -1.0f;
}

void FlyBones::executeState_Lowering() {
    if (timerLowering >= flyDistance) {
        speed.y = 0.0f;
        doStateChange(&FlyBones::StateID_IdleLowered);
    } else {
        timerLowering += 1;
    }
}

void FlyBones::endState_Lowering() { }

//* IdleLowered state

void FlyBones::beginState_IdleLowered() {
    timerIdleLowered = 0;
    gravity = 0.0f;
    maxSpeed.y = 0.0f;
}

void FlyBones::executeState_IdleLowered() {
    if (timerIdleLowered >= idleTime)
        doStateChange(&FlyBones::StateID_Rising);
    else
        timerIdleLowered += 1;
}

void FlyBones::endState_IdleLowered() { }

//* Rising state
void FlyBones::beginState_Rising() {
    timerRising = 0;
    gravity = 0.0875f;
    maxSpeed.y = 1.0f;
}

void FlyBones::executeState_Rising() {
    u16 riseDistance = flyDistance / 2;

    if (timerRising >= riseDistance) {
        speed.y = 0.0f;
        doStateChange(&FlyBones::StateID_IdleRaised);
    } else {
        timerRising += 1;
    }
}

void FlyBones::endState_Rising() { }

//* IdleRaised state

void FlyBones::beginState_IdleRaised() {
    timerIdleRaised = 0;
    gravity = 0.0f;
    maxSpeed.y = 0.0f;
}

void FlyBones::executeState_IdleRaised() {
    if (timerIdleRaised >= idleTime)
        doStateChange(&FlyBones::StateID_Lowering);
    else
        timerIdleRaised += 1;
}

void FlyBones::endState_IdleRaised() { }

//* Die state

void FlyBones::beginState_Die() {
    removeHitboxColliders();
}

void FlyBones::executeState_Die() {
        Vec3 posKillFix(0.0f, -8.0f, 0.0f);

        ActorBuildInfo dryBones = { 0 };
        dryBones.profile = Profile::get(ProfileId::Sprite137);
        dryBones.position = position + posKillFix;
        ActorMgr::instance->create(&dryBones, 0);

        isDeleted = true;

        return;
}

void FlyBones::endState_Die() { }
