#include <game/actor/stage/enemy.h>
#include <game/graphics/model/model.h>
#include <game/sound.h>
#include <game/collision/actorphysicsmgr.h>
#include <game/graphics/drawmgr.h>
#include <game/effect/effect.h>
#include <math.h>
#include <sead.h>

class FallingChestnut : public Enemy {
public:
    FallingChestnut(const ActorBuildInfo* buildInfo);
    virtual ~FallingChestnut() { }
    
    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    ModelWrapper* mModel;
    u32 mDespawnDelay;

    static const HitboxCollider::Info collisionInfo;
    static const ActorPhysicsMgr::Sensor belowSensor;

    DECLARE_STATE(FallingChestnut, Idle);
    DECLARE_STATE(FallingChestnut, Falling);
    DECLARE_STATE(FallingChestnut, OnGround);
};

CREATE_STATE(FallingChestnut, Idle);
CREATE_STATE(FallingChestnut, Falling);
CREATE_STATE(FallingChestnut, OnGround);

const Profile FallingChestnutProfile(&FallingChestnut::build, ProfileID::FallingChestnut, "FallingChestnut", nullptr, 0);
PROFILE_RESOURCES(ProfileID::FallingChestnut, "iga_kuribo");

const HitboxCollider::Info FallingChestnut::collisionInfo = {
    Vec2f(0.0f, -3.0f), Vec2f(12.0f, 15.0f), HitboxCollider::ShapeRectangle, 5, 0, 0x824F, 0x20208, 0, &FallingChestnut::collisionCallback
};

const ActorPhysicsMgr::Sensor FallingChestnut::belowSensor = {
    16.0f, 16.0f, -16.0f
};

FallingChestnut::FallingChestnut(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
{ }

Actor* FallingChestnut::build(const ActorBuildInfo* buildInfo) {
    return new FallingChestnut(buildInfo);
}

u32 FallingChestnut::onCreate() {
    this->mModel = ModelWrapper::create("iga_kuribo", "iga_kuribo");
    
    this->mHitboxCollider.init(this, &FallingChestnut::collisionInfo, 0);
    this->addHitboxColliders();

    this->mPhysicsMgr.init(this, &FallingChestnut::belowSensor);

    this->doStateChange(&StateID_Idle);

    return 1;
}

u32 FallingChestnut::onExecute() {
    Vec3f posOffset(0.0f, -16.0f, 0.0f);
    Vec3u rotOffset(0x40000000, 0, 0);

    Mtx34 mtx;
    mtx.rotateAndTranslate(this->mRotation + rotOffset, this->mPosition + posOffset);

    this->mModel->setMtx(mtx);
    this->mModel->setScale(this->mScale);
    this->mModel->updateModel();

    this->mStates.execute();

    return 1;
}

u32 FallingChestnut::onDraw() {
    DrawMgr::instance()->drawModel(this->mModel);

    return 1;
}

/* STATE: Idle */

void FallingChestnut::beginState_Idle() { }

void FallingChestnut::executeState_Idle() {
    Vec2f dist;

    if (this->distanceToPlayer(dist) > -1 && fabs2f(dist.x) < 48.0f)
        this->doStateChange(&StateID_Falling);
    
    else if (this->distanceToPlayer(dist) > -1 && fabs2f(dist.x) < 80.0f)
        ;   // TODO: Shake
}

void FallingChestnut::endState_Idle() { }

/* STATE: Falling */

void FallingChestnut::beginState_Falling() {
    this->mGravity = -0.1875f;
    this->mMaxSpeed.y = -4.0f;
}

void FallingChestnut::executeState_Falling() {
    this->handleGravity();
    this->handleSpeed();

    this->mPhysicsMgr.processCollisions();

    if (this->mPhysicsMgr.isOnGround()) {
        this->mSpeed.y = 0.0f;
        this->doStateChange(&StateID_OnGround);
    }
}

void FallingChestnut::endState_Falling() { }

/* STATE: OnGround */

void FallingChestnut::beginState_OnGround() { }

void FallingChestnut::executeState_OnGround() {
    this->mDespawnDelay++;

    if (this->mDespawnDelay >= 60) {
        Vec3f effectPos(this->mPosition.x, this->mPosition.y - 18.0f, 4500.0f);
        Effect::spawn(RP_ObakeDoor_Disapp, &effectPos);

        this->mIsDeleted = true;
    }
}

void FallingChestnut::endState_OnGround() { }
