#include "game/actor/stage/enemy.h"
#include "game/actor/stage/playerbase.h"
#include "game/actor/actormgr.h"
#include "game/graphics/model/blendingmodel.h"
#include "game/effect/effect.h"
#include "sead/random.h"
#include "log.h"

class PoisonPiranhaProjectile : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(PoisonPiranhaProjectile, Enemy);

public:
    PoisonPiranhaProjectile(const ActorBuildInfo* buildInfo);
    virtual ~PoisonPiranhaProjectile() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void collisionEnemy(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    static const HitboxCollider::Info collisionInfo;

    struct {
        ModelWrapper* ball;
        ModelWrapper* puddle;
    } model;
    Vec2f baseline;
    u32 timer;

    DECLARE_STATE(PoisonPiranhaProjectile, Ball);
    DECLARE_STATE(PoisonPiranhaProjectile, Puddle);
};

CREATE_STATE(PoisonPiranhaProjectile, Ball);
CREATE_STATE(PoisonPiranhaProjectile, Puddle);

const HitboxCollider::Info PoisonPiranhaProjectile::collisionInfo = {
    0, 5.0f, HitboxCollider::Shape::Circle, 5, 0, 0x824F, 0xFFFBFFFF, 0, &Enemy::collisionCallback
};

class PoisonPiranha : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(PoisonPiranha, Enemy);

public:
    PoisonPiranha(const ActorBuildInfo* buildInfo);
    virtual ~PoisonPiranha() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    BlendingModel* model;
    u32 timer;

    static const HitboxCollider::Info collisionInfo;

    DECLARE_STATE(PoisonPiranha, Idle);
    DECLARE_STATE(PoisonPiranha, Attack);
};

CREATE_STATE(PoisonPiranha, Idle);
CREATE_STATE(PoisonPiranha, Attack);

REGISTER_PROFILE(PoisonPiranha, ProfileID::PoisonPiranha);
PROFILE_RESOURCES(ProfileID::PoisonPiranha, Profile::LoadResourcesAt::Course, "pakkun", "poisball", "e_poison");

const HitboxCollider::Info PoisonPiranha::collisionInfo = {
    Vec2f(0.0f, 16.0f), Vec2f(5.0f, 16.0f), HitboxCollider::Shape::Rectangle, 0x3, 0x0, 0xA4F, 0xFFFAFFFF, 0x2, &Enemy::collisionCallback
};

PoisonPiranha::PoisonPiranha(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , timer(0)
{ }

u32 PoisonPiranha::onCreate() {
    this->position += Vec2f(8.0f, -16.0f);

    this->model = BlendingModel::create("pakkun", "pakkun", 2);

    this->hitboxCollider.init(this, &PoisonPiranha::collisionInfo);
    this->addHitboxColliders();

    this->doStateChange(&PoisonPiranha::StateID_Idle);

    return this->onExecute();
}

u32 PoisonPiranha::onExecute() {
    this->states.execute();

    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);

    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateModel();
    this->model->updateAnimations();
    
    return 1;
}

u32 PoisonPiranha::onDraw() {
    this->model->draw();
    
    return 1;
}

/** STATE: Idle */

void PoisonPiranha::beginState_Idle() {
    this->model->setSklAnim("fire_wait_up", 10.0f);
    this->timer = 190;
}

void PoisonPiranha::executeState_Idle() {
    if (this->timer > 0) {
        this->timer--;
    } else {
        this->doStateChange(&PoisonPiranha::StateID_Attack);
    }

    this->direction = this->directionToPlayerH(this->position);
    sead::Mathu::chase(&this->rotation.y, Direction::directionToRotationList[this->direction], fixDeg(2.0f));
}

void PoisonPiranha::endState_Idle() { }

/** STATE: Attack */

void PoisonPiranha::beginState_Attack() {
    this->timer = 106;
    this->model->setSklAnim("fire_attack_up", 4.0f);
}

void PoisonPiranha::executeState_Attack() {
    if (this->timer > 0) {
        this->timer--;
    
        if (this->timer == 75) {
            const f32 sign = this->direction == Direction::Left ? -1.0f : 1.0f;

            ActorBuildInfo buildInfo = { 0 };
            buildInfo.position = this->position + Vec3f(14.0f * sign, -22.0f, 0.0f);
            buildInfo.profile = Profile::get(ProfileID::PoisonPiranhaProjectile);

            static_cast<StageActor*>(ActorMgr::instance()->create(buildInfo))->direction = this->direction;
        }
    } else {
        this->doStateChange(&PoisonPiranha::StateID_Idle);
    }
}

void PoisonPiranha::endState_Attack() { }

/** PROJECTILE: / POISON: */

REGISTER_PROFILE(PoisonPiranhaProjectile, ProfileID::PoisonPiranhaProjectile);

PoisonPiranhaProjectile::PoisonPiranhaProjectile(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , baseline(buildInfo->position.x, buildInfo->position.y)
    , timer(600)
{ }

u32 PoisonPiranhaProjectile::onCreate() {
    this->scale = 0.5f;

    this->model.ball = ModelWrapper::create("poisball", "poisball", 1);
    this->model.puddle = ModelWrapper::create("e_poison", "e_poison", 1);

    PhysicsMgr::Sensor belowSensor = { -4, 4, 0 };
    PhysicsMgr::Sensor sideSensor = { -4, 4, 7 };
    PhysicsMgr::Sensor aboveSensor = { -4, 4, 7 };
    this->physicsMgr.init(this, &belowSensor, &aboveSensor, &sideSensor);

    this->hitboxCollider.init(this, &PoisonPiranhaProjectile::collisionInfo);
    this->addHitboxColliders();

    this->doStateChange(&PoisonPiranhaProjectile::StateID_Ball);

    return this->onExecute();
}

u32 PoisonPiranhaProjectile::onExecute() {
    this->states.execute();

    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);

    this->model.ball->setMtx(mtx);
    this->model.ball->setScale(this->scale);
    this->model.ball->updateModel();
    this->model.ball->updateAnimations();

    this->model.puddle->setMtx(mtx);
    this->model.puddle->setScale(this->scale);
    this->model.puddle->updateModel();
    this->model.puddle->updateAnimations();

    if (this->timer == 0) {
        this->isDeleted = true;
        
        Vec3f effectScale = 0.5f;
        Effect::spawn(RP_Cmn_PoisonSplash_00, &this->position, nullptr, &effectScale);
    } else {
        this->timer--;
    }

    return 1;
}

u32 PoisonPiranhaProjectile::onDraw() {
    if (this->states.currentState()->isEqual(PoisonPiranhaProjectile::StateID_Ball)) {
        this->model.ball->draw();
    } else {
        this->model.puddle->draw();
    }

    return 1;
}

void PoisonPiranhaProjectile::collisionEnemy(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (hcOther->owner->getProfileID() == ProfileID::PoisonPiranhaProjectile) {
        this->isDeleted = true;
    }
}

void PoisonPiranhaProjectile::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    Vec3f effectScale = 0.5f;
    Effect::spawn(RP_Cmn_PoisonSplash_00, &this->position, nullptr, &effectScale);

    Enemy::collisionPlayer(hcSelf, hcOther);
}

bool PoisonPiranhaProjectile::collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    hcOther->owner->isDeleted = true;
    this->isDeleted = true;
    
    return false;
}

bool PoisonPiranhaProjectile::collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionPlayer(hcSelf, hcOther);

    return false;
}

/** STATE: Ball */

void PoisonPiranhaProjectile::beginState_Ball() {
    this->model.ball->playSklAnim("idle");
}

void PoisonPiranhaProjectile::executeState_Ball() { 
    const f32 widthFraction = 3.0f / 20.0f;
    const f32 arcHeight = 16.0f * 3.0f;
    const f32 sign = this->direction == Direction::Right ? 1.0f : -1.0f;

    this->position.x += sign;
    this->position.y = -pow2f(widthFraction * ((this->position.x - this->baseline.x) + (arcHeight * -sign))) + this->baseline.y + 2.0f * arcHeight;

    this->physicsMgr.processCollisions();
    if (this->physicsMgr.isOnGround()) {
        this->doStateChange(&PoisonPiranhaProjectile::StateID_Puddle);
    }
}

void PoisonPiranhaProjectile::endState_Ball() { }

/** STATE: Puddle */

void PoisonPiranhaProjectile::beginState_Puddle() {
    this->model.puddle->playSklAnim("idle");
    this->hitboxCollider.colliderInfo.shape = HitboxCollider::Shape::Rectangle;
    this->hitboxCollider.colliderInfo.radius = Vec2f(10.0f, 4.0f);

    Vec3f effectScale = 0.5f;
    Effect::spawn(RP_Cmn_PoisonSplash_00, &this->position, nullptr, &effectScale);
}

void PoisonPiranhaProjectile::executeState_Puddle() { }

void PoisonPiranhaProjectile::endState_Puddle() { }
