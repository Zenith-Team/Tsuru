#include "game/actor/stage/enemy.h"
#include "game/graphics/model/model.h"
#include "game/effect/effect.h"
#include "game/graphics/model/animation.h"
#include "log.h"

class Splunkin : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(Splunkin, Enemy);

public:
    Splunkin(const ActorBuildInfo* buildInfo);
    virtual ~Splunkin() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    // collisions later
    bool collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    static HitboxCollider::Info collisionInfo;
    

    void updateModel();

    ModelWrapper* model;
    bool damaged;
    bool frozen;
    u32 frozenCounter;
    DECLARE_STATE(Splunkin, Walk);
    DECLARE_STATE(Splunkin, Turn);
    DECLARE_STATE(Splunkin, Die);
};

CREATE_STATE(Splunkin, Walk);
CREATE_STATE(Splunkin, Turn);
CREATE_STATE(Splunkin, Die);

const Profile SplunkinProfile(&Splunkin::build, ProfileID::Splunkin);
// actual splunkin resource here, just waiting for rod to make it
PROFILE_RESOURCES(ProfileID::Splunkin, Profile::LoadResourcesAt_Course, "kakibo");

// collider stuff
bool Splunkin::collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->frozen = true;
    return Enemy::collisionIceball(hcSelf, hcOther);
}
HitboxCollider::Info Splunkin::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0f, 8.0f), HitboxCollider::HitboxShape_Rectangle, 5, 0, 0x824F, 0xFFFFFFFF, 0, &Enemy::collisionCallback
};

// important

Splunkin::Splunkin(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , damaged(false)
    , frozen(false)
    , frozenCounter(0)
{ }

Actor* Splunkin::build(const ActorBuildInfo* buildInfo) {
    return new Splunkin(buildInfo);
}

u32 Splunkin::onCreate() {
    this->damaged = (this->settings1 >> 0x1C & 0xF); // nybble 5

    this->model = ModelWrapper::create("kakibo", "kakibo", 5);
    this->model->playSklAnim("walk0");
    this->model->loopSklAnims(true);
    this->position.y -= 8;
    this->position.x += 8;
    this->rotation.y += 20;


    this->hitboxCollider.init(this, &Splunkin::collisionInfo);
    this->addHitboxColliders();

    this->doStateChange(&Splunkin::StateID_Walk);
    this->updateModel();
    return 1;
}

u32 Splunkin::onExecute() {
    this->states.execute();
    this->updateModel();
    if (frozen) {
        this->model->sklAnims[0]->speed = 0.0;
        if (this->frozenCounter == 0)
            this->position.y += 16;
        this->frozenCounter++;
        if (this->frozenCounter == 500) {
            this->model->sklAnims[0]->speed = 1.0;
            this->frozenCounter = 0;
            this->frozen = false;
            // this->position.y -= 8;
        }
    }
    return 1;
}

u32 Splunkin::onDraw() {
    this->model->draw();
    return 1;
}

void Splunkin::updateModel() {
    Mtx34 mtx;
    Vec3f modelPos = this->position;
    if (!this->frozen)
        modelPos.y -= 8;
    mtx.makeRTIdx(this->rotation, modelPos);
    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateAnimations();
    this->model->updateModel();
}

// states

/** STATE: Walk */


void Splunkin::beginState_Walk() {

}
void Splunkin::executeState_Walk() {

}
void Splunkin::endState_Walk() {

}

/** STATE: Turn */

void Splunkin::beginState_Turn() {

}
void Splunkin::executeState_Turn() {

}
void Splunkin::endState_Turn() {

}


/** STATE: Die */

void Splunkin::beginState_Die() {
    
}
void Splunkin::executeState_Die() {
    
}
void Splunkin::endState_Die() {
    
}