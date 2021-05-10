#include "actor/enemy.h"

#include "actormgr.h"
#include "sound.h"
#include "effect.h"
#include "drawmgr.h"
#include "movementhandler.h"


class FallingChestnut : public Enemy {
public:
    FallingChestnut(const ActorBuildInfo* buildInfo);
    virtual ~FallingChestnut() { }

    static ActorBase* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void updateModel();

    ModelWrapper* model;
    MovementHandler movementHandler;

    static const ActiveCollider::Info collisionInfo;

    static const CollisionMgr::Sensor belowSensor;

    u32 despawnDelay;

    DECLARE_STATE(FallingChestnut, Evaluate);
    DECLARE_STATE(FallingChestnut, Falling);
    DECLARE_STATE(FallingChestnut, OnGround);
};

CREATE_STATE(FallingChestnut, Evaluate);
CREATE_STATE(FallingChestnut, Falling);
CREATE_STATE(FallingChestnut, OnGround);

const Profile FallingChestnutProfile(&FallingChestnut::build, ProfileId::Sprite692, "FallingChestnut", nullptr, 0);
PROFILE_RESOURCES(ProfileId::Sprite692, "iga_kuribo");

const ActiveCollider::Info FallingChestnut::collisionInfo = { Vec2(0.0f, -3.0f), Vec2(12.0f, 15.0f), 0, 5, 0, 0x824F, 0x20208, 0, &FallingChestnut::collisionCallback };

const CollisionMgr::Sensor FallingChestnut::belowSensor = { 16.0f, 16.0f, -16.0f };

FallingChestnut::FallingChestnut(const ActorBuildInfo* buildInfo) : Enemy(buildInfo) { }

ActorBase* FallingChestnut::build(const ActorBuildInfo* buildInfo) {
    return new FallingChestnut(buildInfo);
}

u32 FallingChestnut::onCreate() {
    model = ModelWrapper::create("iga_kuribo", "iga_kuribo", 0, 0);

    aCollider.init(this, &FallingChestnut::collisionInfo, 0);
    addActiveColliders();

    collisionMgr.init(this, &FallingChestnut::belowSensor, nullptr, nullptr);

    u32 movementMask = movementHandler.getMaskForMovementType(settings2 & 0xFF);
    movementHandler.link(position, movementMask, movementId);

    updateModel();

    doStateChange(&StateID_Evaluate);

    return 1;
}

u32 FallingChestnut::onExecute() {
    movementHandler.execute();
    states.execute();

    updateModel();

    return 1;
}

u32 FallingChestnut::onDraw() {
    DrawMgr::instance->drawModel(model);

    return 1;
}

void FallingChestnut::updateModel() {
    model->updateAnimations();

    Vec3 posOffset(0.0f, -16.0f, 0.0f);
    Vec3 rotOffset(-90.0f, 0.0f, 0.0f);

    Mtx34 mtx;
    mtx.rotateAndTranslate(rotation + rotOffset, position + posOffset);

    model->setMtx(mtx);
    model->setScale(scale);
    model->updateModel();
}


// Idle state

void FallingChestnut::beginState_Evaluate() { }

void FallingChestnut::executeState_Evaluate() {
    Vec2 dist;

    if (distanceToPlayer(dist) > -1 && fabs(dist.x) < 48.0f) {
        doStateChange(&StateID_Falling);
    }

    else if (distanceToPlayer(dist) > -1 && fabs(dist.x) < 80.0f) {

    }
}

void FallingChestnut::endState_Evaluate() { }


//* Falling state

void FallingChestnut::beginState_Falling() {
    gravity = -0.1875f;
    maxSpeed.y = -4.0;
}

void FallingChestnut::executeState_Falling() {
    handleGravity();
    handleSpeed();

    collisionMgr.process();

    if (collisionMgr.isOnGround()) {
        speed.y = 0;
        doStateChange(&StateID_OnGround);
    }
}

void FallingChestnut::endState_Falling() { }


//* OnGround state

void FallingChestnut::beginState_OnGround() { }

void FallingChestnut::executeState_OnGround() {
    despawnDelay += 1;

    if (despawnDelay >= 60) {
        Vec3 effectPos(position.x, position.y - 18.0f, 4500.0f);
        Effect::spawn(921, &effectPos, nullptr, nullptr);

        isDeleted = true;
    }
}

void FallingChestnut::endState_OnGround() { }
