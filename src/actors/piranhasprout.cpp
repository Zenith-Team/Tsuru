#include "game/actor/stage/enemy.h"
#include "game/actor/actormgr.h"
#include "game/graphics/model/blendingmodel.h"
#include "game/effect/effect.h"
#include "tsuru/easing.h"
#include "tsuru/log.h"

/**
 * * Known bugs:
 * - Projectile hitbox is incorrect for the first frame
*/

class PiranhaSproutProjectile : public Enemy {
    SEAD_RTTI_OVERRIDE(PiranhaSproutProjectile, Enemy);

public:
    PiranhaSproutProjectile(const ActorBuildInfo* buildInfo);
    virtual ~PiranhaSproutProjectile() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    bool collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    u32 die();

    static const HitboxCollider::Info collisionInfo;

    ModelWrapper* model;
    sead::Vector2f baseline;
};

const HitboxCollider::Info PiranhaSproutProjectile::collisionInfo = {
    sead::Vector2f(0.0f, 0.0f), sead::Vector2f(5.0f, 5.0f), HitboxCollider::Shape::Circle, 5, 0, 0x824F, 0xFFFBFFFF, 0, &Enemy::collisionCallback
};

class PiranhaSprout : public Enemy {
    SEAD_RTTI_OVERRIDE(PiranhaSprout, Enemy);

public:
    PiranhaSprout(const ActorBuildInfo* buildInfo);
    virtual ~PiranhaSprout() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    void collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    BlendingModel* model;
    u32 timer;

    static const HitboxCollider::Info collisionInfo;

    DECLARE_STATE(PiranhaSprout, Idle);
    DECLARE_STATE(PiranhaSprout, Attack);
    DECLARE_STATE(PiranhaSprout, Die);
};

CREATE_STATE(PiranhaSprout, Idle);
CREATE_STATE(PiranhaSprout, Attack);
CREATE_STATE(PiranhaSprout, Die);

REGISTER_PROFILE(PiranhaSprout, ProfileID::PiranhaSprout);
PROFILE_RESOURCES(ProfileID::PiranhaSprout, Profile::LoadResourcesAt::Course, "nukunuku", "nukubomb");

const HitboxCollider::Info PiranhaSprout::collisionInfo = {
    sead::Vector2f(0.0f, 0.0f), sead::Vector2f(12.0f, 4.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0xFFFBFFFF, 0, &Enemy::collisionCallback
};

PiranhaSprout::PiranhaSprout(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , timer(0)
{ }

u32 PiranhaSprout::onCreate() {
    this->scale = sead::Vector3f(0.17f, 0.17f, 0.17f);
    this->position.x += 8.0f;
    this->position.z -= 4000.0f;
    this->direction = this->directionToPlayerH(this->position);

    if (this->eventID1 >> 0x4 & 0x1) {
        this->rotation.z = sead::Mathf::deg2idx(180.0f);
        this->rotation.y = Direction::directionToRotationList[!this->direction];
    } else {
        this->rotation.y = Direction::directionToRotationList[this->direction];
    }

    this->model = BlendingModel::create("nukunuku", "nukunuku", 2);

    this->hitboxCollider.init(this, &PiranhaSprout::collisionInfo);
    this->addHitboxColliders();

    this->doStateChange(&PiranhaSprout::StateID_Idle);

    return this->onExecute();
}

u32 PiranhaSprout::onExecute() {
    this->states.execute();

    sead::Matrix34f mtx;
    mtx.makeRTIdx(this->rotation, this->position);

    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateModel();
    this->model->updateAnimations();

    this->model->model->getBoneWorldMatrix(this->model->model->searchBoneIndex("Crest"), &mtx);
    sead::Vector3f bonePos(mtx.m[0][3], mtx.m[1][3], mtx.m[2][3]);

    const f32 sign = this->eventID1 >> 0x4 & 0x1 ? -1.0f : 1.0f;
    this->hitboxCollider.colliderInfo.offset = sead::Vector2f(bonePos.x - this->position.x, bonePos.y - this->position.y - (6.5f * sign));
    
    return 1;
}

u32 PiranhaSprout::onDraw() {
    this->model->draw();

    return 1;
}

void PiranhaSprout::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    u32 hitType = this->processCollision(hcSelf, hcOther, 0);

    if (hitType == HitType::Collide) {
        this->damagePlayer(hcSelf, hcOther);
    } else if (hitType == HitType::NormalJump || hitType == HitType::SpinJump) {
        this->killPlayerJump(hcOther->owner, sead::Vector3f(0.0f, 0.0f, 0.0f), &PiranhaSprout::StateID_Die);
    }
}

void PiranhaSprout::collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionPlayer(hcSelf, hcOther);
}

/** STATE: Idle */

void PiranhaSprout::beginState_Idle() {
    this->timer = 360;
    this->model->setSklAnim("Wait", 10.0f);
    this->model->loopSklAnims(true);
}

void PiranhaSprout::executeState_Idle() {
    if (this->timer > 0) {
        this->timer--;
    } else {
        this->doStateChange(&PiranhaSprout::StateID_Attack);
    }
}

void PiranhaSprout::endState_Idle() {
    this->model->loopSklAnims(false);
}

/** STATE: Attack */

void PiranhaSprout::beginState_Attack() {
    this->model->setSklAnim("AttackSign", 10.0f);
    this->timer = 20;
}

void PiranhaSprout::executeState_Attack() {
    if (this->model->sklAnims[1]->frameCtrl.currentFrame == 39.0f && this->timer == 20) {
        ActorBuildInfo buildInfo = { 0 };
        buildInfo.position = this->position + sead::Vector3f(this->direction == Direction::Right ? 14.0f : -14.0f, (this->eventID1 >> 0x4 & 0x1) ? 16.0f : -16.0f, 4000.0f);
        buildInfo.eventID1 = this->eventID1;
        buildInfo.profile = Profile::get(ProfileID::PiranhaSproutProjectile);
        
        static_cast<StageActor*>(ActorMgr::instance()->create(buildInfo))->direction = this->direction;

        this->timer--;
    }

    if (this->timer < 20) {
        this->timer--;
    }

    if (this->timer == 0) {
        this->doStateChange(&PiranhaSprout::StateID_Idle);
    }
}

void PiranhaSprout::endState_Attack() { }

/** STATE: Die */

void PiranhaSprout::beginState_Die() {
    this->model->setSklAnim("PullOut", 4.0f);
    this->removeHitboxColliders();
}

void PiranhaSprout::executeState_Die() {
    if ((this->model->sklAnims[0]->frameCtrl.currentFrame / this->model->sklAnims[0]->frameCtrl.endFrame) >= 0.5f) {
        sead::Vector3f effectPos(this->position.x, this->position.y, 4500.0f);
        sead::Vector3f effectScale = sead::Vector3f(0.5f, 0.5f, 0.5f);
        Effect::spawn(RP_Jugemu_CloudDisapp, &effectPos, nullptr, &effectScale);
        this->isDeleted = true;
    }
}

void PiranhaSprout::endState_Die() { }

/** PROJECTILE: */

REGISTER_PROFILE(PiranhaSproutProjectile, ProfileID::PiranhaSproutProjectile);

PiranhaSproutProjectile::PiranhaSproutProjectile(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , baseline(buildInfo->position.x, buildInfo->position.y)
{ }

u32 PiranhaSproutProjectile::onCreate() {
    this->scale = sead::Vector3f(0.17f, 0.17f, 0.17f);
    this->position.x += 8.0f;
    this->position.z -= 4000.0f;

    this->model = ModelWrapper::create("nukubomb", "nukubomb");

    PhysicsMgr::Sensor belowSensor = { -4, 4, -7 };
    PhysicsMgr::Sensor sideSensor = { -4, 4, 7 };
    PhysicsMgr::Sensor aboveSensor = { -4, 4, 7 };
    this->physicsMgr.init(this, &belowSensor, &aboveSensor, &sideSensor);

    this->hitboxCollider.init(this, &PiranhaSproutProjectile::collisionInfo);
    this->addHitboxColliders();

    return this->onExecute();
}

u32 PiranhaSproutProjectile::onExecute() {
    this->rotation.z += sead::Mathf::deg2idx((1.0f / (sead::Mathf::abs(this->position.y - this->baseline.y) / 10.0f)) * 16.0f);

    static const f32 widthFraction = 3.0f/20.0f;
    static const f32 arcHeight = 16.0f * 3;
    const f32 sign = this->direction == Direction::Right ? 1.0f : -1.0f;

    // Parabola arc
    this->position.x += sign;
    if (this->eventID1 >> 0x4 & 0x1) {
        this->position.y = sead::Mathf::pow(widthFraction * ((this->position.x - this->baseline.x) + (arcHeight * -sign)), 2.0f) + this->baseline.y - 2.0f * arcHeight;
    } else {
        this->position.y = -sead::Mathf::pow(widthFraction * ((this->position.x - this->baseline.x) + (arcHeight * -sign)), 2.0f) + this->baseline.y + 2.0f * arcHeight;
    }

    this->physicsMgr.processCollisions();
    if (this->physicsMgr.isCollidedLeft() || this->physicsMgr.isCollidedRight() || this->physicsMgr.isOnGround()) {
        this->die();
    }

    sead::Matrix34f mtx;
    mtx.makeRTIdx(this->rotation, this->position);

    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateModel();

    return 1;
}

u32 PiranhaSproutProjectile::onDraw() {
    this->model->draw();

    return 1;
}

bool PiranhaSproutProjectile::collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    hcOther->owner->isDeleted = true;
    
    return false;
}

u32 PiranhaSproutProjectile::die() {
    Effect::spawn(RP_Block_break_chika, &this->position);
    this->isDeleted = true;
    
    return 0;
}
