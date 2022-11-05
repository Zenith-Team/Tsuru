#include "game/actor/stage/enemy.h"
#include "game/graphics/model/modelnw.h"
#include "game/graphics/drawmgr.h"
#include "game/effect/effect.h"

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
    void collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionPenguinSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionGroundPoundYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionPropellerDrill(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionFireballYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

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
    Vec2f(0.0f, -4.0f), Vec2f(16.0f, 16.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0xFFFFFF, 0x20208, 0, &Enemy::collisionCallback
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
    u32 hitType = this->processCollision(hcSelf, hcOther, 0);

    if (hitType == Enemy::HitType::Collide) {
        this->damagePlayer(hcSelf, hcOther);
    } else if (hitType == Enemy::HitType::NormalJump || hitType == Enemy::HitType::SpinJump) {
        this->killPlayerJump(hcOther->owner, 0.0f, &Scuttlebug::StateID_Die);
    }
}

void Scuttlebug::collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    u32 hitType = this->processCollision(hcSelf, hcOther, 0);

    if (hitType == Enemy::HitType::Collide) {
        this->damagePlayer(hcSelf, hcOther);
    } else if (hitType == Enemy::HitType::NormalJump || hitType == Enemy::HitType::SpinJump) {
        this->killPlayerJump(hcOther->owner, 0.0f, &Scuttlebug::StateID_Die);
    }
}

bool Scuttlebug::collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return this->collisionStar(hcSelf, hcOther);
}

bool Scuttlebug::collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    Vec3f effectOrigin(this->position.x, this->position.y, 4500.0f);
    Vec3f effectPos(effectOrigin);
    Effect::spawn(RP_Jugemu_CloudDisapp, &effectPos, nullptr, &this->scale);

    this->isDeleted = true;

    return true;
}

bool Scuttlebug::collisionSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return this->collisionStar(hcSelf, hcOther);
}

bool Scuttlebug::collisionPenguinSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return this->collisionStar(hcSelf, hcOther);
}

bool Scuttlebug::collisionGroundPoundYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return this->collisionStar(hcSelf, hcOther);
}

bool Scuttlebug::collisionPropellerDrill(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return this->collisionStar(hcSelf, hcOther);
}

bool Scuttlebug::collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return this->collisionStar(hcSelf, hcOther);
}

bool Scuttlebug::collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    Enemy::collisionFireball(hcSelf, hcOther);

    return true;
}

bool Scuttlebug::collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->doStateChange(&Scuttlebug::StateID_Die);

    return true;
}

bool Scuttlebug::collisionFireballYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return this->collisionFireball(hcSelf, hcOther);
}

/** STATE: Die */

void Scuttlebug::beginState_Die() {
    this->removeHitboxColliders();
    this->isDeleted = true;
}

void Scuttlebug::executeState_Die() { }

void Scuttlebug::endState_Die() { }
