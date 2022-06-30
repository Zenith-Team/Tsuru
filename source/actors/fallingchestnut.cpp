#include "game/actor/stage/enemy.h"
#include "game/graphics/model/model.h"
#include "game/collision/actorphysicsmgr.h"
#include "game/graphics/drawmgr.h"
#include "game/effect/effect.h"
#include "math.h"

class FallingChestnut : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(FallingChestnut, Enemy)

public:
    FallingChestnut(const ActorBuildInfo* buildInfo);
    virtual ~FallingChestnut() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    ModelWrapper* model;
    u32 despawnDelay;

    static const HitboxCollider::Info collisionInfo;
    static const ActorPhysicsMgr::Sensor belowSensor;

    DECLARE_STATE(FallingChestnut, Idle);
    DECLARE_STATE(FallingChestnut, Falling);
    DECLARE_STATE(FallingChestnut, OnGround);
};

CREATE_STATE(FallingChestnut, Idle);
CREATE_STATE(FallingChestnut, Falling);
CREATE_STATE(FallingChestnut, OnGround);

const Profile FallingChestnutProfile(&FallingChestnut::build, ProfileID::FallingChestnut);
PROFILE_RESOURCES(ProfileID::FallingChestnut, Profile::LoadResourcesAt_Course, "iga_kuribo");

const HitboxCollider::Info FallingChestnut::collisionInfo = {
    Vec2f(0.0f, -3.0f), Vec2f(12.0f, 15.0f), HitboxCollider::HitboxShape_Rectangle, 5, 0, 0x824F, 0x20208, 0, &FallingChestnut::collisionCallback
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
    this->model = ModelWrapper::create("iga_kuribo", "iga_kuribo");

    this->hitboxCollider.init(this, &FallingChestnut::collisionInfo, 0);
    this->addHitboxColliders();

    this->physicsMgr.init(this, &FallingChestnut::belowSensor);

    this->doStateChange(&StateID_Idle);

    return 1;
}

u32 FallingChestnut::onExecute() {
    Vec3f posOffset(0.0f, -16.0f, 0.0f);
    Vec3u rotOffset(fixDeg(90.0f), 0, 0);

    Mtx34 mtx;
    mtx.rotateAndTranslate(this->rotation + rotOffset, this->position + posOffset);

    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateModel();

    this->states.execute();

    return 1;
}

u32 FallingChestnut::onDraw() {
    DrawMgr::instance()->drawModel(this->model);

    return 1;
}

/* STATE: Idle */

void FallingChestnut::beginState_Idle() { }

void FallingChestnut::executeState_Idle() {
    Vec2f dist;

    if (this->distanceToPlayer(dist) > -1 && abs(dist.x) < 48.0f)
        this->doStateChange(&StateID_Falling);

    else if (this->distanceToPlayer(dist) > -1 && abs(dist.x) < 80.0f)
        ;   // TODO: Shake
}

void FallingChestnut::endState_Idle() { }

/* STATE: Falling */

void FallingChestnut::beginState_Falling() {
    this->gravity = -0.1875f;
    this->maxSpeed.y = -4.0f;
}

void FallingChestnut::executeState_Falling() {
    this->handleGravity();
    this->handleSpeed();

    this->physicsMgr.processCollisions();

    if (this->physicsMgr.isOnGround()) {
        this->speed.y = 0.0f;
        this->doStateChange(&StateID_OnGround);
    }
}

void FallingChestnut::endState_Falling() { }

/* STATE: OnGround */

void FallingChestnut::beginState_OnGround() { }

void FallingChestnut::executeState_OnGround() {
    this->despawnDelay++;

    if (this->despawnDelay >= 60) {
        Vec3f effectPos(this->position.x, this->position.y - 18.0f, 4500.0f);
        Effect::spawn(RP_ObakeDoor_Disapp, &effectPos);

        this->isDeleted = true;
    }
}

void FallingChestnut::endState_OnGround() { }
