#include "game/actor/stage/enemy.h"
#include "game/graphics/model/modelnw.h"
#include "game/effect/effect.h"
#include "game/graphics/model/animation.h"
#include "tsuru/log.h"

class Flaptor : public Enemy {
    SEAD_RTTI_OVERRIDE(Flaptor, Enemy);

public:
    ENUM_CLASS(MoveType,
        Stationary,
        Horizontal,
        Vertical
    );

public:
    Flaptor(const ActorBuildInfo* buildInfo);
    virtual ~Flaptor() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    static const HitboxCollider::Info collisionInfo;

    ModelWrapper* model;
    sead::Vector3f startPosition;
    f32 threshold;
    f32 timer;
    u8 moveType;

    DECLARE_STATE(Flaptor, Idle);
    DECLARE_STATE(Flaptor, Dive);
    DECLARE_STATE(Flaptor, DieSquish);
    DECLARE_STATE(Flaptor, Die);
    DECLARE_STATE(Flaptor, Land);
};

CREATE_STATE(Flaptor, Idle);
CREATE_STATE(Flaptor, Dive);
CREATE_STATE(Flaptor, DieSquish);
CREATE_STATE(Flaptor, Die);
CREATE_STATE(Flaptor, Land);

REGISTER_PROFILE(Flaptor, ProfileID::Flaptor);
PROFILE_RESOURCES(ProfileID::Flaptor, Profile::LoadResourcesAt::Course, "mokinger");

const HitboxCollider::Info Flaptor::collisionInfo = {
    sead::Vector2f(0.0f, 0.0f), sead::Vector2f(10.0f, 10.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0xFFFBFFFF, 0, &Enemy::collisionCallback
};

Flaptor::Flaptor(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , startPosition()
    , threshold()
    , timer(0.0f)
    , moveType()
{ }

u32 Flaptor::onCreate() {
    this->model = ModelWrapper::create("mokinger", "mokinger", 1);

    this->hitboxCollider.init(this, &Flaptor::collisionInfo);
    this->addHitboxColliders();

    PhysicsMgr::Sensor belowSensor = { -8, 8, -8 };
    this->physicsMgr.init(this, &belowSensor);

    this->startPosition = this->position;
    this->threshold = (this->eventID1 >> 0x4 & 0xF) * 16.0f; // nybble 1
    this->moveType = this->eventID1 & 0xF; // nybble 2

    this->direction = Direction::Right;
    this->scale = sead::Vector3f(0.175f, 0.175f, 0.175f);

    if (this->moveType > MoveType::Vertical) {
        PRINT(LogColor::Red, "Flaptor invalid move type");
        return 2;
    }

    this->doStateChange(&Flaptor::StateID_Idle);

    return this->onExecute();
}

u32 Flaptor::onExecute() {
    sead::Matrix34f mtx;
    mtx.makeRTIdx(this->rotation, this->position + sead::Vector3f(0.0f, -8.0f, 0.0f));

    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateModel();
    this->model->updateAnimations();

    this->timer++;

    this->states.execute();

    return 1;
}

u32 Flaptor::onDraw() {
    this->model->draw();

    return 1;
}

void Flaptor::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    u32 hitType = this->processCollision(hcSelf, hcOther, 0);
    if (hitType == HitType::Collide) {
        this->damagePlayer(hcSelf, hcOther);
    } else {
        this->killPlayerJump(hcOther->owner, sead::Vector3f(0.0f, 0.0f, 0.0f), &Flaptor::StateID_DieSquish);
    }
}

/** STATE: Idle */

void Flaptor::beginState_Idle() {
    this->model->playSklAnim("Fly");
}

void Flaptor::executeState_Idle() {
    switch (this->moveType) {
        case MoveType::Stationary: {
            sead::Mathu::chase(&this->rotation.y, Direction::directionToRotationList[this->directionToPlayerH(this->position)], sead::Mathf::deg2idx(4.0f));

            sead::Mathf::chase(&this->position.x, this->startPosition.x, 1.0f);
            sead::Mathf::chase(&this->position.y, this->startPosition.y, 1.0f);

            break;
        }

        case MoveType::Horizontal: {
            sead::Mathu::chase(&this->rotation.y, Direction::directionToRotationList[this->direction], sead::Mathf::deg2idx(4.0f));

            if (this->position.x - this->startPosition.x < -(this->threshold)) {
                this->direction = Direction::Right;
            } else if (this->position.x - this->startPosition.x > (this->threshold)) {
                this->direction = Direction::Left;
            }

            if (this->direction == Direction::Right) {
                this->position.x++;
            } else {
                this->position.x--;
            }

            if (!sead::Mathf::chase(&this->position.y, this->startPosition.y, 1.0f)) {
                return;
            }

            break;
        }

        case MoveType::Vertical: {
            sead::Mathu::chase(&this->rotation.x, Direction::directionToRotationList[this->direction], sead::Mathf::deg2idx(4.0f));

            if (this->position.y - this->startPosition.y < -(this->threshold)) {
                this->direction = Direction::Up;
            } else if (this->position.y - this->startPosition.y > (this->threshold)) {
                this->direction = Direction::Down;
            }

            if (this->direction == Direction::Up) {
                this->position.y++;
            } else {
                this->position.y--;
            }

            if (!sead::Mathf::chase(&this->position.x, this->startPosition.x, 1.0f)) {
                return;
            }

            break;
        }
    }

    if (this->distanceToPlayer().length() <= 5.0f * 16.0f && this->distanceToPlayer().y < 4.0f) {
        this->doStateChange(&Flaptor::StateID_Dive);
    }
}

void Flaptor::endState_Idle() { }

/** STATE: Dive */

void Flaptor::beginState_Dive() {
    this->gravity = -0.1875f;
    this->maxSpeed.y = -4.0f;

    this->model->playSklAnim("Attack");
}

void Flaptor::executeState_Dive() {
    this->handlePhysics();
    this->physicsMgr.processCollisions();

    if (this->physicsMgr.isOnGround()) {
        this->doStateChange(&Flaptor::StateID_Land);
    }
}

void Flaptor::endState_Dive() { }

/** STATE: Land */

void Flaptor::beginState_Land() {
    this->model->playSklAnim("AttackLand");
    this->model->loopSklAnims(false);
}

void Flaptor::executeState_Land() {
    if (this->model->sklAnims[0]->frameCtrl.isDone()) {
        this->doStateChange(&Flaptor::StateID_Idle);
    }
}

void Flaptor::endState_Land() {
    this->model->loopSklAnims(true);
}

/** STATE: DieSquish */

void Flaptor::beginState_DieSquish() {
    this->model->playSklAnim("PressDown");
    this->model->loopSklAnims(false);

    this->removeHitboxColliders();
}

void Flaptor::executeState_DieSquish() {
    if (this->model->sklAnims[0]->frameCtrl.isDone()) {
        this->isDeleted = true;
    }
}

void Flaptor::endState_DieSquish() { }

/** STATE: Die */

void Flaptor::beginState_Die() { }

void Flaptor::executeState_Die() {
    this->isDeleted = true;
}

void Flaptor::endState_Die() { }
