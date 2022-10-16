#include "game/actor/stage/enemy.h"
#include "game/graphics/model/modelnw.h"
#include "game/effect/effect.h"
#include "game/graphics/model/animation.h"
#include "log.h"

class Flaptor : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(Flaptor, Enemy);

public:
    ENUM_CLASS(MoveType,
        Stationary,
        Horizontal,
        Vertical
    );

public:
    Flaptor(const ActorBuildInfo* buildInfo);
    virtual ~Flaptor() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    static const HitboxCollider::Info collisionInfo;

    ModelWrapper* model;
    Vec3f startPosition;
    f32 threshold;
    f32 timer;
    u32 wait;
    u8 moveType;

    DECLARE_STATE(Flaptor, Idle);
    DECLARE_STATE(Flaptor, Dive);
    DECLARE_STATE(Flaptor, Swoop);
    DECLARE_STATE(Flaptor, DieSquish);
    DECLARE_STATE(Flaptor, Die);
};

CREATE_STATE(Flaptor, Idle);
CREATE_STATE(Flaptor, Dive);
CREATE_STATE(Flaptor, Swoop);
CREATE_STATE(Flaptor, DieSquish);
CREATE_STATE(Flaptor, Die);

const Profile FlaptorProfile(&Flaptor::build, ProfileID::Flaptor);
PROFILE_RESOURCES(ProfileID::Flaptor, Profile::LoadResourcesAt::Course, "moking");

const HitboxCollider::Info Flaptor::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0, 8.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0xFFFFFFFF, 0, &Enemy::collisionCallback
};

Flaptor::Flaptor(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , startPosition()
    , threshold()
    , timer(0.0f)
    , moveType()
{ }

Actor* Flaptor::build(const ActorBuildInfo* buildInfo) {
    return new Flaptor(buildInfo);
}

u32 Flaptor::onCreate() {
    // this->model = ModelWrapper::create("star_coin", "star_coinA");
    this->model = ModelWrapper::create("moking", "moking");
    
    this->hitboxCollider.init(this, &Flaptor::collisionInfo);
    this->addHitboxColliders();
    
    PhysicsMgr::Sensor belowSensor = { -8, 8, -8 };
    this->physicsMgr.init(this, &belowSensor);

    this->startPosition = this->position;
    this->threshold = (this->eventID1 >> 0x4 & 0xF) * 16.0f; // nybble 1
    this->moveType = this->eventID1 & 0xF; // nybble 2

    model->setScale(0.001);
    this->direction = Direction::Right;

    if (this->moveType > MoveType::Vertical) {
        PRINT(LogColor::Red, "Flaptor invalid move type");
        return 2;
    }

    this->doStateChange(&Flaptor::StateID_Idle);

    return this->onExecute();
}

u32 Flaptor::onExecute() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);

    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateModel();

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
        this->killPlayerJump(hcOther->owner, 0.0f, &Flaptor::StateID_DieSquish);
    }
}

/** STATE: Idle */

void Flaptor::beginState_Idle() { }

void Flaptor::executeState_Idle() {
    switch (this->moveType) {
        case MoveType::Stationary: {
            sead::Mathu::chase(&this->rotation.y, Direction::directionToRotationList[this->directionToPlayerH(this->position)], fixDeg(4.0f));

            break;
        }

        case MoveType::Horizontal: {
            sead::Mathu::chase(&this->rotation.y, Direction::directionToRotationList[this->direction], fixDeg(4.0f));
        
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
            sead::Mathu::chase(&this->rotation.x, Direction::directionToRotationList[this->direction], fixDeg(4.0f));
        
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

    if (this->distanceToPlayer().length() <= 5.f*16.f && this->distanceToPlayer().y < 4.0f) {
        //if (this->moveType == MoveType::Vertical || this->moveType == MoveType::Horizontal) {
            //this->doStateChange(&Flaptor::StateID_Swoop);   
        //} else {
            this->doStateChange(&Flaptor::StateID_Dive);
        //}
    }
}

void Flaptor::endState_Idle() { }

/** STATE: Dive */

void Flaptor::beginState_Dive() {
    this->gravity = -0.1875f;
    this->maxSpeed.y = -4.0f;

    this->wait = 100;
}

void Flaptor::executeState_Dive() {
    this->handlePhysics();
    this->physicsMgr.processCollisions();

    if (this->physicsMgr.isOnGround()) {
        this->wait--;
    }

    if (this->wait == 0) {
        this->doStateChange(&Flaptor::StateID_Idle);
    }
}

void Flaptor::endState_Dive() { }

/** STATE: Swoop */

void Flaptor::beginState_Swoop() { }
void Flaptor::executeState_Swoop() { }
void Flaptor::endState_Swoop() { }

/** STATE: DieSquish */

void Flaptor::beginState_DieSquish() { }
void Flaptor::executeState_DieSquish() { }
void Flaptor::endState_DieSquish() { }

/** STATE: Die */

void Flaptor::beginState_Die() { }
void Flaptor::executeState_Die() { }
void Flaptor::endState_Die() { }


// 