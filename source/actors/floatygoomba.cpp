#include "game/actor/stage/enemy.h"
#include "game/graphics/model/modelnw.h"
#include "game/actor/stage/playerbase.h"
#include "game/effect/effect.h"
#include "game/audio/gameaudio.h"

class FloatyGoomba : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(FloatyGoomba, Enemy);

public:
    FloatyGoomba(const ActorBuildInfo* buildInfo);
    virtual ~FloatyGoomba() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    bool collisionIceball(HitboxCollider*, HitboxCollider*) override { return false; }

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    ModelWrapper* floaty;
    ModelWrapper* model;
    f32 t;
    bool onlyFloaty;

    DECLARE_STATE(FloatyGoomba, Die);
};

CREATE_STATE(FloatyGoomba, Die);

REGISTER_PROFILE(FloatyGoomba, ProfileID::FloatyGoomba);
PROFILE_RESOURCES(ProfileID::FloatyGoomba, Profile::LoadResourcesAt::Course, "ukibofloat", "kuribo");

FloatyGoomba::FloatyGoomba(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , onlyFloaty(buildInfo->eventID1 >> 0x4 & 0x1) // nybble 1
{ }

u32 FloatyGoomba::onCreate() {
    static const HitboxCollider::Info collisionInfo = {
        0.0f, 10.0f, HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0xFFFBFFFF, 0, &FloatyGoomba::collisionCallback
    };

    this->hitboxCollider.init(this, &collisionInfo);
    this->addHitboxColliders();

    this->floaty = ModelWrapper::create("ukibofloat", "ukibofloat");

    if (!this->onlyFloaty) {
        this->model = ModelWrapper::create("kuribo", "kuribo", 1);
        this->model->playSklAnim("hikkuri");
    }

    return this->onExecute();
}

u32 FloatyGoomba::onExecute() {
    Mtx34 mtx;
    
    mtx.makeRTIdx(this->rotation, this->position);
    this->floaty->setMtx(mtx);
    this->floaty->setScale(0.17f);
    this->floaty->updateModel();

    if (this->model) {
        mtx.makeRTIdx(this->rotation, this->position + Vec3f(0.0f, -2.25f, 0.0f));
        this->model->setMtx(mtx);
        this->model->setScale(this->scale);
        this->model->updateModel();
        this->model->updateAnimations();
    }

    // Bob up and down
    this->position.y += sinf(++this->t * 0.025f) * 0.07f;

    if (!this->onlyFloaty && this->model) {
        this->direction = this->directionToPlayerH(this->position);

        if (this->distanceToPlayer().length() > 6.f*16.f || !this->model) {
            sead::Mathu::chase(&this->rotation.y, 0, fixDeg(1.25f));
        } else {
            sead::Mathu::chase(&this->rotation.y, Direction::directionToRotationList[this->direction], fixDeg(2.5f));
            sead::Mathf::chase(&this->position.x, this->distanceToPlayer().x + this->position.x, 0.25f);
        }
    }

    return 1;
}
        
u32 FloatyGoomba::onDraw() {
    if (this->model) {
        this->model->draw();
    }

    this->floaty->draw();

    return 1;
}

void FloatyGoomba::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (this->onlyFloaty || (this->model == nullptr && hcOther->owner->position.y - this->position.y > 0.0f)) {
        hcOther->owner->speed.y = 4.0f;
        GameAudio::startSoundEmy(SoundEffects::SE_PLY_RIDE_CLOUD, this->position);

        return;
    }

    Enemy::HitType::__type__ hit = this->processCollision(hcSelf, hcOther);

    if (hit == Enemy::HitType::Collide) {
        return this->damagePlayer(hcSelf, hcOther);
    } else {
        this->killPlayerJump(hcOther->owner, 0.0f, &FloatyGoomba::StateID_Die);
    }
}

bool FloatyGoomba::collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (this->onlyFloaty) {
        hcOther->owner->speed.y = 4.0f;
        GameAudio::startSoundEmy(SoundEffects::SE_PLY_RIDE_CLOUD, this->position);
        
        return false;
    }

    if (this->model) {
        this->killPlayerJump(hcOther->owner, 0.0f, &FloatyGoomba::StateID_Die);

        return false;
    }

    this->isDeleted = true;
    
    Effect::spawn(RP_Balloon_Burst_0, &this->position, &this->rotation, &this->scale);

    return false;
}

/** STATE: Die */

void FloatyGoomba::beginState_Die() {
    if (this->eventID1 >> 0x4 & 0x1) {
        this->isDeleted = true;
        return;
    }

    this->model = nullptr;

    this->hitboxCollider.colliderInfo.radius.y /= 1.5f;
    this->hitboxCollider.colliderInfo.radius.x++;
}

void FloatyGoomba::executeState_Die() { }

void FloatyGoomba::endState_Die() { }
