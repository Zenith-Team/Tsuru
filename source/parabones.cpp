#include "game/actor/enemy.h"

#include "game/actormgr.h"
#include "game/direction.h"
#include "game/graphics/drawmgr.h"

class ParaBones : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(ParaBones, Enemy)

public:
    ParaBones(const ActorBuildInfo* pBuildInfo);
    virtual ~ParaBones() { }

    static BaseActor* build(const ActorBuildInfo* pBuildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void collisionPlayer(HitboxCollider* pHCSelf, HitboxCollider* pHCOther) override;

    void modelUpdate();

    ModelWrapper* mModel;
    u32 mTimerIdleLowered;
    u32 mTimerIdleRaised;
    u32 mTimerLowering;
    u32 mTimerRising;
    u16 mFlyDistance;
    u16 mIdleTime;

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

const HitboxCollider::Info ParaBones::sCollisionInfo = { Vec2f(0.0f, 0.0f), Vec2f(16.0f, 16.0f), HitboxCollider::Circle, 3, 0, 0xFFFFFFFF, 0xFFFFFFFF, 0, &Enemy::collisionCallback };

ParaBones::ParaBones(const ActorBuildInfo* pBuildInfo)
    : Enemy(pBuildInfo)
{ }

BaseActor* ParaBones::build(const ActorBuildInfo* pBuildInfo) {
    return new ParaBones(pBuildInfo);
}

u32 ParaBones::onCreate() {
    Vec3u rotationOffset(0, 1000, 0);
    this->mRotation.y = directionToRotationList[Direction::Left];

    mModel = ModelWrapper::create("nokonokoB", "nokonokoB", 10);
    mModel->playSklAnim("flyA", 0);

    mHitboxCollider.init(this, &ParaBones::sCollisionInfo, nullptr);
    addHitboxColliders();

    mFlyDistance = 200;
    mIdleTime = 150;

    doStateChange(&ParaBones::StateID_Lowering);

    modelUpdate();

    return 1;
}

u32 ParaBones::onExecute() {
    handleGravity();
    handleSpeed();

    if (mTimerLowering >= mFlyDistance)
        mSpeed.y = 0.0f;
    else
        mTimerLowering += 1;

    mStates.execute();

    modelUpdate();

    return 1; 
}

u32 ParaBones::onDraw() {
    DrawMgr::sInstance->drawModel(mModel);

    return 1;
}

void ParaBones::modelUpdate() {
    Mtx34 mtx;

    mtx.rotateAndTranslate(mRotation, mPosition);

    mModel->setMtx(mtx);
    mModel->setScale(mScale);
    mModel->updateModel();
    mModel->updateAnimations();
}

void ParaBones::collisionPlayer(HitboxCollider* pHCSelf, HitboxCollider* pHCOther) {
    u32 hitType = processCollision(pHCSelf, pHCOther, 0);

    if (hitType == 0)
        damagePlayer(pHCSelf, pHCOther);
    else if (hitType == 1 || hitType == 3)
        killPlayerJump(pHCOther->mOwner, 0.0f, &ParaBones::StateID_Die);
}

// Lowering state

void ParaBones::beginState_Lowering() {
    mTimerLowering = 0;
    mGravity = -1.0f;
    mMaxSpeed.y = -1.0f;
}

void ParaBones::executeState_Lowering() {
    if (mTimerLowering >= mFlyDistance) {
        mSpeed.y = 0.0f;
        doStateChange(&ParaBones::StateID_IdleLowered);
    }
    
    else
        mTimerLowering++;
}

void ParaBones::endState_Lowering() { }


// IdleLowered state

void ParaBones::beginState_IdleLowered() {
    mTimerIdleLowered = 0;
    mGravity = 0.0f;
    mMaxSpeed.y = 0.0f;
}

void ParaBones::executeState_IdleLowered() {
    if (mTimerIdleLowered >= mIdleTime)
        doStateChange(&ParaBones::StateID_Rising);
    else
        mTimerIdleLowered++;
}

void ParaBones::endState_IdleLowered() { }


// Rising state

void ParaBones::beginState_Rising() {
    mTimerRising = 0;
    mGravity = 0.0875f;
    mMaxSpeed.y = 1.0f;
}

void ParaBones::executeState_Rising() {
    if (mTimerRising >= mFlyDistance / 2) {
        mSpeed.y = 0.0f;
        doStateChange(&ParaBones::StateID_IdleRaised);
    }

    else
        mTimerRising++;
}

void ParaBones::endState_Rising() { }


// IdleRaised state

void ParaBones::beginState_IdleRaised() {
    mTimerIdleRaised = 0;
    mGravity = 0.0f;
    mMaxSpeed.y = 0.0f;
}

void ParaBones::executeState_IdleRaised() {
    if (mTimerIdleRaised >= mIdleTime)
        doStateChange(&ParaBones::StateID_Lowering);
    else
        mTimerIdleRaised++;
}

void ParaBones::endState_IdleRaised() { }


// Die state

void ParaBones::beginState_Die() {
    removeHitboxColliders();
    Vec3f posKillFix(0.0f, -8.0f, 0.0f);

    ActorBuildInfo DryBones = { 0 };
    DryBones.mProfile = Profile::get(Profile::spriteToProfileList[137]);
    DryBones.mPosition += posKillFix;
    ActorMgr::sInstance->create(&DryBones, 0);
    this->mIsDeleted = true;
}

void ParaBones::executeState_Die() { }

void ParaBones::endState_Die() { }
