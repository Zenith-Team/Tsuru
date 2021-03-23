#include "actor/enemy.h"

#include "movementhandler.h"
#include "eventmgr.h"
#include "drawmgr.h"
#include "sound.h"
#include "model.h"

class FireThwomp : public Enemy {
public:
    FireThwomp(const ActorBuildInfo* buildInfo);
    virtual ~FireThwomp() { }

    static Base* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void updateModel();

    ModelWrapper* model;
    MovementHandler movementHandler;

    static const ActiveCollider::Info collisionInfo;

    static const CollisionMgr::Sensor bottomSensor;
    static const CollisionMgr::Sensor topSensor;

    DECLARE_STATE(FireThwomp, Idle)
    DECLARE_STATE(FireThwomp, Falling)
    DECLARE_STATE(FireThwomp, Rising)
};

CREATE_STATE(FireThwomp, Idle);
CREATE_STATE(FireThwomp, Falling);
CREATE_STATE(FireThwomp, Rising);

const Profile FireThwompProfile(&FireThwomp::build, ProfileId::Sprite405, "FireThwomp", nullptr, 0);
PROFILE_RESOURCES(ProfileId::Sprite405, "iga_kuribo");

const ActiveCollider::Info FireThwomp::collisionInfo = { Vec2(0.0f, -3.0f), Vec2(12.0f, 15.0f), 0, 5, 0, 0x824F, 0x20208, 0, &FireThwomp::collisionCallback };

const CollisionMgr::Sensor FireThwomp::bottomSensor = { 16.0f, 16.0f, -16.0f };
const CollisionMgr::Sensor FireThwomp::topSensor = { 16.0f, 16.0f, 16.0f };

FireThwomp::FireThwomp(const ActorBuildInfo* buildInfo) : Enemy(buildInfo) { }

Base* FireThwomp::build(const ActorBuildInfo* buildInfo) {
    return new FireThwomp(buildInfo);
}

u32 FireThwomp::onCreate() {
    model = ModelWrapper::create("iga_kuribo", "iga_kuribo", 0, 0);

    aCollider.init(this, &FireThwomp::collisionInfo, 0);
    addActiveColliders();

    collisionMgr.init(this, &FireThwomp::bottomSensor, &FireThwomp::topSensor, nullptr);

    u32 movementMask = movementHandler.getMaskForMovementType(settings2 & 0xFF);
    movementHandler.link(position, movementMask, movementId);

    updateModel();

    doStateChange(&StateID_Idle);

    return 1;
}

u32 FireThwomp::onExecute() {
    movementHandler.execute();
    states.execute();

    updateModel();

    return 1;
}

u32 FireThwomp::onDraw() {
    DrawMgr::instance->drawModel(model);

    return 1;
}

void FireThwomp::updateModel() {
    model->updateAnimations();

    Vec3 posOffset(0.0f, -16.0f, 0.0f);
    Vec3 rotOffset(0.0f, 0.0f, 0.0f);

    Mtx34 mtx;
    mtx.rotateAndTranslate(rotation + rotOffset, position + posOffset);

    model->setMtx(mtx);
    model->setScale(scale);
    model->updateModel();
}


void FireThwomp::beginState_Idle() { }

void FireThwomp::executeState_Idle() {
    Vec2 dist;

    if (distanceToPlayer(dist) > -1 && fabs(dist.x) < 64.0f) {
        doStateChange(&StateID_Falling);
    }
}

void FireThwomp::endState_Idle() { }


void FireThwomp::beginState_Falling() {
    gravity = -0.1875f;
    maxSpeed.y = -4.0;
}

void FireThwomp::executeState_Falling() {
    handleGravity();
    handleSpeed();

    collisionMgr.process();

    if (collisionMgr.isOnGround()) {
        speed.y = 0;
        doStateChange(&StateID_Rising);
    }
}

void FireThwomp::endState_Falling() { }


void FireThwomp::beginState_Rising() {
    gravity = 0.1875f;
    maxSpeed.y = 1.0;
}

void FireThwomp::executeState_Rising() {
    handleGravity();
    handleSpeed();

    collisionMgr.process();

    if (collisionMgr.isOnGround()) {
        speed.y = 0;
        doStateChange(&StateID_Idle);
    }
}

void FireThwomp::endState_Rising() { }
