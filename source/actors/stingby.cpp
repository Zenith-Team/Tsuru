#include "game/actor/stage/enemy.h"
#include "game/graphics/model/modelnw.h"
#include "game/effect/effect.h"

class Stingby : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(Stingby, Enemy);

public:
    Stingby(const ActorBuildInfo* buildInfo);
    virtual ~Stingby() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    static const HitboxCollider::Info collisionInfo;

    ModelWrapper* model;
    Vec3f idleCenter;

    DECLARE_STATE(Stingby, Idle);
    DECLARE_STATE(Stingby, Chase);
    DECLARE_STATE(Stingby, Die);
};

CREATE_STATE(Stingby, Idle);
CREATE_STATE(Stingby, Chase);
CREATE_STATE(Stingby, Die);

const Profile StingbyProfile(&Stingby::build, ProfileID::Stingby);
PROFILE_RESOURCES(ProfileID::Stingby, Profile::LoadResourcesAt::Course, "star_coin");

const HitboxCollider::Info Stingby::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0f, 8.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0xFFFFFFFF, 0, &Enemy::collisionCallback
};

Stingby::Stingby(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , idleCenter(buildInfo->position)
{ }

Actor* Stingby::build(const ActorBuildInfo* buildInfo) {
    return new Stingby(buildInfo);
}

u32 Stingby::onCreate() {
    this->model = ModelWrapper::create("star_coin", "star_coinA");
    this->direction = Direction::Right;

    this->hitboxCollider.init(this, &collisionInfo);
    this->addHitboxColliders();

    this->doStateChange(&Stingby::StateID_Idle);

    return this->onExecute();
}

u32 Stingby::onExecute() {
    this->states.execute();

    sead::Mathu::chase(&this->rotation.y, Direction::directionToRotationList[this->direction], 0x11FFFFF);

    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);

    this->model->setMtx(mtx);
    this->model->updateModel();
    this->model->updateAnimations();

    return 1;
}

u32 Stingby::onDraw() {
    this->model->draw();
    
    return 1;
}

void Stingby::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    u32 hitType = this->processCollision(hcSelf, hcOther, 0);
    if (hitType == HitType::Collide)
        this->damagePlayer(hcSelf, hcOther);
    else if (hitType == HitType::NormalJump || hitType == HitType::SpinJump)
        this->killPlayerJump(hcOther->owner, 0.0f, &Stingby::StateID_Die);
}

/** STATE: Idle */

void Stingby::beginState_Idle() {
    this->idleCenter = this->position;
    this->direction = Direction::Right;
}

void Stingby::executeState_Idle() {
    if (sead::Mathf::abs(this->distanceToPlayer().x) < 5.5*16) {
        this->doStateChange(&Stingby::StateID_Chase);
    }

    if (this->direction == Direction::Right) {
        this->position.x += 0.5f;
        if (this->position.x > this->idleCenter.x + 4*16)
            this->direction = Direction::Left;
    } else {
        this->position.x -= 0.5f;
        if (this->position.x < this->idleCenter.x - 4*16)
            this->direction = Direction::Right;
    }
}

void Stingby::endState_Idle() { }

/** STATE: Chase */

void Stingby::beginState_Chase() { }

void Stingby::executeState_Chase() {
    if (sead::Mathf::abs(this->distanceToPlayer().x) > 6*16) {
        this->doStateChange(&Stingby::StateID_Idle);
    }

    this->position.x += (this->distanceToPlayer().x > 0) ? 0.5f : -0.5f;
    this->direction = !(this->distanceToPlayer().x > 0);
}

void Stingby::endState_Chase() { }

/** STATE: Die */

void Stingby::beginState_Die() { }

void Stingby::executeState_Die() {
    Vec3f effectPos(this->position.x, this->position.y, 4500.0f);
    Vec3f effectScale = this->scale / 2;
    Effect::spawn(RP_Jugemu_CloudDisapp, &effectPos, nullptr, &effectScale);
    this->isDeleted = true;
}

void Stingby::endState_Die() { }