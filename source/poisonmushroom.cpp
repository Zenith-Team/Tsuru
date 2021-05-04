#include "actor/enemy.h"

#include "drawmgr.h"

class PoisonMushroom : public Enemy {
    //SEAD_RTTI_OVERRIDE(PoisonMushroom, Enemy) //? wants vtable for some reason
public:
    PoisonMushroom(const ActorBuildInfo* buildInfo);
    virtual ~PoisonMushroom() { }

    static ActorBase* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    // Collision Conditions
    bool collisionGroundPound(ActiveCollider* acSelf, ActiveCollider* acOther) override;

    void updateModel();

    ModelWrapper* model;

    static const CollisionMgr::Sensor PoisonMushroom::bottomSensor;
    static const CollisionMgr::Sensor PoisonMushroom::topSensor;
    static const CollisionMgr::Sensor PoisonMushroom::sideSensor;

    static const ActiveCollider::Info collisionInfo;

    DECLARE_STATE(PoisonMushroom, Move)
    DECLARE_STATE(PoisonMushroom, Turn)
};

CREATE_STATE(PoisonMushroom, Move)
CREATE_STATE(PoisonMushroom, Turn)

const ActorInfo PoisonMushroomActorInfo = { Vec2i(8, -16), Vec2i(0, 16), Vec2i(8, 16), 0, 0, 0, 0, 0 };
const Profile PoisonMushroomProfile(&PoisonMushroom::build, ProfileId::Sprite306, "PoisonMushroom", &PoisonMushroomActorInfo, 0);
PROFILE_RESOURCES(ProfileId::Sprite306, "I_kinoko");

const ActiveCollider::Info PoisonMushroom::collisionInfo = { Vec2(0.0f, 8.0f), Vec2(8.0f, 8.0f), 1, 3, 0, 0xFFFFFFFF, 0xFFFFFFFF, 0, &Enemy::collisionCallback };

const CollisionMgr::Sensor PoisonMushroom::bottomSensor     = { 8.0f,  8.0f,   0.0f };
const CollisionMgr::Sensor PoisonMushroom::topSensor        = { 0.0f,  0.0f,   0.0f };
const CollisionMgr::Sensor PoisonMushroom::sideSensor       = { 0.0f,  16.0f,  8.0f };

PoisonMushroom::PoisonMushroom(const ActorBuildInfo* buildInfo) : Enemy(buildInfo) { }

ActorBase* PoisonMushroom::build(const ActorBuildInfo* buildInfo) {
    return new PoisonMushroom(buildInfo);
}

u32 PoisonMushroom::onCreate() {
    model = ModelWrapper::create("I_kinoko", "I_kinoko", 5);
    model->playSklAnim("wait", 0);

    direction = directionToPlayerH(position);

    aCollider.init(this, &PoisonMushroom::collisionInfo, nullptr);
    addActiveColliders();

    gravity = -0.1875f;
    maxSpeed.y = -4.0f;

    collisionMgr.init(this, &PoisonMushroom::bottomSensor, &PoisonMushroom::topSensor, &PoisonMushroom::sideSensor);

    doStateChange(&PoisonMushroom::StateID_Move);

    updateModel();

    return 1;
}

u32 PoisonMushroom::onExecute() {
    handleGravity();
    handleSpeed();

    collisionMgr.process();

    rotation.y = directionToRotationList[direction];

    if (collisionMgr.isOnGround()) {
        speed.y = 0.0f;
    }

    updateModel();

    return 1;
}

u32 PoisonMushroom::onDraw() {
    DrawMgr::instance->drawModel(model);

    return 1;
}

void PoisonMushroom::updateModel() {
    Mtx34 mtx;
    mtx.rotateAndTranslate(rotation, position);

    model->setMtx(mtx);
    model->setScale(scale);
    model->updateModel();
    model->updateAnimations();
}

bool PoisonMushroom::collisionGroundPound(ActiveCollider* acSelf, ActiveCollider* acOther) {
    damagePlayer(acSelf, acOther);
}

//* Move state

void PoisonMushroom::beginState_Move() {
    speed.x = -1.0f;
    maxSpeed.x = -1.0f;
}

void PoisonMushroom::executeState_Move() { }

void PoisonMushroom::endState_Move() { }

//* Turn state

void PoisonMushroom::beginState_Turn() {
    if (collisionMgr.isCollidedLeft()) {
        speed.x = -1.0f;
        maxSpeed.x = -1.0f;
    } else if (collisionMgr.isCollidedRight()) {
        speed.x = 1.0f;
        maxSpeed.x = 1.0f;
    }
}

void PoisonMushroom::executeState_Turn() { doStateChange(&StateID_Move); }

void PoisonMushroom::endState_Turn() { }
