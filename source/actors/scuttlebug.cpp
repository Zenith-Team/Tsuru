#include "game/actor/stage/enemy.h"
#include "game/graphics/model/modelnw.h"
#include "game/graphics/drawmgr.h"
#include "log.h"

class Scuttlebug : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(Scuttlebug, Enemy);

public:
    Scuttlebug(const ActorBuildInfo* buildInfo);
    virtual ~Scuttlebug() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    static const HitboxCollider::Info collisionInfo;

    ModelWrapper* model;
    ModelWrapper* string;
    Vec3f startPos;

    DECLARE_STATE(Scuttlebug, Die);
};

CREATE_STATE(Scuttlebug, Die);

const Profile ScuttlebugProfile(&Scuttlebug::build, ProfileID::Scuttlebug);
PROFILE_RESOURCES(ProfileID::Scuttlebug, Profile::LoadResourcesAt::Course, "gasagoso");

const HitboxCollider::Info Scuttlebug::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(16.0f, 16.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0x20208, 0, &Enemy::collisionCallback
};

Scuttlebug::Scuttlebug(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
{ }

Actor* Scuttlebug::build(const ActorBuildInfo* buildInfo) {
    return new Scuttlebug(buildInfo);
}

u32 Scuttlebug::onCreate() {
    this->rotation = Vec3u(fixDeg(90.0f), 0, 0);
    this->startPos = this->position;

    this->hitboxCollider.init(this, &collisionInfo);
    this->addHitboxColliders();

    this->gravity = -0.1875f;
    this->maxSpeed.y = -4.0f;

    this->model = ModelWrapper::create("gasagoso", "gasagoso", 1);
    this->string = ModelWrapper::create("gasagoso", "string");

    this->model->playSklAnim("walk");

    return this->onExecute();
}

u32 Scuttlebug::onExecute() {
    Mtx34 mtx;

    mtx.makeRTIdx(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->setScale(this->scale * 2.5f);
    this->model->updateModel();
    this->model->updateAnimations();

    mtx.makeRTIdx(this->rotation, this->position);
    this->string->setMtx(mtx);
    this->string->setScale(this->scale * 2.5f);
    this->string->updateModel();

    this->handlePhysics();

    if (sead::Mathf::abs(this->position.y - this->startPos.y) > ((this->eventID1 >> 0x4 & 0xF) * 16.0f)) {
        this->maxSpeed.y = 0;
    }

    return 1;
}

u32 Scuttlebug::onDraw() {
    this->model->draw();
    this->string->draw();

    return 1;
}

void Scuttlebug::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    u32 hitType = this->processCollision(hcSelf, hcOther);

    if (hitType == 0) {
        this->damagePlayer(hcSelf, hcOther);
    } else {
        this->killPlayerJump(hcOther->owner, 0.0f, &Scuttlebug::StateID_Die);
    }
}

/** STATE: Die */

void Scuttlebug::beginState_Die() {
    this->isDeleted = true;
}

void Scuttlebug::executeState_Die() { }

void Scuttlebug::endState_Die() { }
