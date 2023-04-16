#include "game/actor/stage/enemy.h"
#include "game/graphics/model/modelnw.h"
#include "game/effect/effect.h"

class Stingby : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(Stingby, Enemy);

public:
    Stingby(const ActorBuildInfo* buildInfo);
    virtual ~Stingby() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    void collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    static const HitboxCollider::Info collisionInfo;

    ModelWrapper* model;
    Vec3f idleCenter;

    DECLARE_STATE(Stingby, Idle);
    DECLARE_STATE(Stingby, Notice);
    DECLARE_STATE(Stingby, Chase);
    DECLARE_STATE(Stingby, Die);
};

CREATE_STATE(Stingby, Idle);
CREATE_STATE(Stingby, Notice);
CREATE_STATE(Stingby, Chase);
CREATE_STATE(Stingby, Die);

REGISTER_PROFILE(Stingby, ProfileID::Stingby);
PROFILE_RESOURCES(ProfileID::Stingby, Profile::LoadResourcesAt::Course, "hacchin000");

const HitboxCollider::Info Stingby::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.5f, 8.5f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0xFFFBFFFF, 0, &Enemy::collisionCallback
};

Stingby::Stingby(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , idleCenter(buildInfo->position)
{ }

u32 Stingby::onCreate() {
    this->model = ModelWrapper::create("hacchin000", "hacchin000", 4);

    this->direction = Direction::Right;
    this->scale = 0.17f;

    this->hitboxCollider.init(this, &collisionInfo);
    this->addHitboxColliders();

    this->doStateChange(&Stingby::StateID_Idle);

    return this->onExecute();
}

u32 Stingby::onExecute() {
    this->states.execute();

    if (this->states.currentState()->ID != Stingby::StateID_Die.ID) {
        sead::Mathu::chase(&this->rotation.y, Direction::directionToRotationList[this->direction], 0x11FFFFF);
    }

    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);

    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
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

    if (hitType == HitType::Collide) {
        this->damagePlayer(hcSelf, hcOther);
    } else if (hitType == HitType::NormalJump || hitType == HitType::SpinJump) {
        this->killPlayerJump(hcOther->owner, 0.0f, &Stingby::StateID_Die);
    }
}

void Stingby::collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionPlayer(hcSelf, hcOther);
}

/** STATE: Idle */

void Stingby::beginState_Idle() {
    this->idleCenter = this->position;
    this->direction = Direction::Right;

    this->model->playSklAnim("fly_idle");
}

void Stingby::executeState_Idle() {
    if (sead::Mathf::abs(this->distanceToPlayer().x) < 5.5f * 16) {
        this->doStateChange(&Stingby::StateID_Notice);
    }

    if (this->direction == Direction::Right) {
        this->position.x += 0.5f;
        if (this->position.x > this->idleCenter.x + 4 * 16) {
            this->direction = Direction::Left;
        }
    } else {
        this->position.x -= 0.5f;
        if (this->position.x < this->idleCenter.x - 4 * 16) {
            this->direction = Direction::Right;
        }
    }
}

void Stingby::endState_Idle() { }

/** STATE: Notice */

void Stingby::beginState_Notice() {
    this->model->playSklAnim("notice");
}

void Stingby::executeState_Notice() {
    if (this->model->sklAnims[0]->frameCtrl.currentFrame == (this->model->sklAnims[0]->frameCtrl.endFrame - 1.0f)) {
        this->doStateChange(&Stingby::StateID_Chase);
    }
}

void Stingby::endState_Notice() { }

/** STATE: Chase */

void Stingby::beginState_Chase() {
    this->model->playSklAnim("fly_dash");
}

void Stingby::executeState_Chase() {
    if (sead::Mathf::abs(this->distanceToPlayer().x) > 6 * 16) {
        this->doStateChange(&Stingby::StateID_Idle);
    }

    this->position.x += (this->distanceToPlayer().x > 0) ? 0.5f : -0.5f;
    this->direction = !(this->distanceToPlayer().x > 0);
}

void Stingby::endState_Chase() { }

/** STATE: Die */

void Stingby::beginState_Die() {
    this->model->playSklAnim("die_squish");
    this->removeHitboxColliders();
}

void Stingby::executeState_Die() {
    if (this->model->sklAnims[0]->frameCtrl.currentFrame == (this->model->sklAnims[0]->frameCtrl.endFrame - 1.0f)) {
        this->isDeleted = true;
    }
}

void Stingby::endState_Die() { }
