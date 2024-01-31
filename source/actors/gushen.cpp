#include "game/actor/stage/enemy.h"
#include "game/graphics/model/modelnw.h"
#include "game/collision/hitboxcollider.h"

class Gushen : public Enemy {
    SEAD_RTTI_OVERRIDE(Gushen, Enemy);

public:
    Gushen(const ActorBuildInfo* buildInfo);
    virtual ~Gushen() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    void updateSprayCollider();

    bool freeze() override;

    static HitboxCollider::Info collisionInfo;

    static void sprayCollisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    DECLARE_STATE(Gushen, Idle);
    DECLARE_STATE(Gushen, Up);
    DECLARE_STATE(Gushen, Die);

    ModelWrapper* model;
    HitboxCollider::Info sprayCollisionInfo;
    HitboxCollider sprayCollider;
    f32 baseline;
    u8 timer;
};

CREATE_STATE(Gushen, Idle);
CREATE_STATE(Gushen, Up);
CREATE_STATE(Gushen, Die);

REGISTER_PROFILE(Gushen, ProfileID::Gushen);
PROFILE_RESOURCES(ProfileID::Gushen, Profile::LoadResourcesAt::Course, "star_coin");

HitboxCollider::Info Gushen::collisionInfo = {
    sead::Vector2f(0.0f, 0.0f), sead::Vector2f(16.0f, 16.0f), HitboxCollider::Shape::Rectangle, 0x3, 0x9, 0x24F, 0xE, 0x1000, &Gushen::collisionCallback
};

Gushen::Gushen(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , sprayCollisionInfo()
    , sprayCollider()
    , baseline(buildInfo->position.y)
    , timer(0)
{ }

u32 Gushen::onCreate() {
    this->model = ModelWrapper::create("star_coin", "star_coinA");

    PhysicsMgr::Sensor belowSensor = { -8, 8, -16 };
    PhysicsMgr::Sensor sideSensor = { -8, 8, 16 };
    PhysicsMgr::Sensor aboveSensor = { -8, 8, 16 };
    this->physicsMgr.init(this, &belowSensor, &aboveSensor, &sideSensor);

    this->hitboxCollider.init(this, &Gushen::collisionInfo);
    this->addHitboxColliders();

    this->doStateChange(&Gushen::StateID_Idle);

    return this->onExecute();
}

u32 Gushen::onExecute() {
    if (!this->states.currentState()->isEqual(Gushen::StateID_Ice)) {
        this->updateSprayCollider();
    }

    this->offscreenDelete(); //? do we need to exempt Ice state?

    this->states.execute();
    this->handlePhysics();
    this->physicsMgr.processCollisions();

    if (this->physicsMgr.isOnGround()) {
        this->speed.y = 0;
    }

    sead::Matrix34f mtx;
    mtx.makeRTIdx(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->updateAnimations();
    this->model->setScale(this->scale);
    this->model->updateModel();

    return 1;
}

u32 Gushen::onDraw() {
    this->model->draw();

    return 1;
}

void Gushen::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    u32 hitType = this->processCollision(hcSelf, hcOther, 0);

    if (hitType == HitType::Collide) {
        this->damagePlayer(hcSelf, hcOther);
    } else if (hitType == HitType::NormalJump || hitType == HitType::SpinJump) {
        this->killPlayerJump(hcOther->owner, sead::Vector3f(0.0f, 0.0f, 0.0f), &Gushen::StateID_Die);
    }
}

void Gushen::sprayCollisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    Gushen* self = static_cast<Gushen*>(hcSelf->owner);

    if (hcOther->owner->type == StageActor::Type::Player) {
        self->damagePlayer(hcSelf, hcOther);
    }
}

void Gushen::updateSprayCollider() {
    const f32 distanceToBaseline = this->position.y - this->baseline;

    this->sprayCollisionInfo.set(
        sead::Vector2f(0.0f, -(distanceToBaseline / 2.0f + Gushen::collisionInfo.radius.y)), sead::Vector2f(8.0f, (distanceToBaseline / 2.0f)), HitboxCollider::Shape::Rectangle, 0x3, 0x9, 0x24F, 0xE, 0x1000, &Gushen::sprayCollisionCallback
    );
    this->sprayCollider.init(this, &this->sprayCollisionInfo);
}

bool Gushen::freeze() {
    EnemyFreezeMgr::Info freezeArg = {
        0, this->position, sead::Vector3f(2.0f, 2.0f, 2.0f), 0
    };

    //this->freezeMgr.freeze(freezeArg, 1);
    
    return 1;
}

/** STATE: Idle */

void Gushen::beginState_Idle() {
    this->timer = 0;
}

void Gushen::executeState_Idle() {
    this->timer++;

    if (this->timer >= 160) {
        this->doStateChange(&Gushen::StateID_Up);
    }
}

void Gushen::endState_Idle() { }

/** STATE: Up */

void Gushen::beginState_Up() {
    this->timer = 0;
    this->gravity = 0.0f;

    this->baseline = this->position.y;
    HitboxColliderMgr::instance()->safeAddToCreateList(&this->sprayCollider);
}

void Gushen::executeState_Up() {
    this->timer++;

    this->speed.y = 1.0f;

    if (this->timer >= 100) {
        this->doStateChange(&Gushen::StateID_Idle);
    }
}

void Gushen::endState_Up() {
    this->gravity = -0.1875f;
    HitboxColliderMgr::instance()->removeFromActiveList(&this->sprayCollider);
}

/** STATE: Die */

void Gushen::beginState_Die() {
    this->isDeleted = true;
}

void Gushen::executeState_Die() { }

void Gushen::endState_Die() { }
