#include "game/actor/stage/enemy.h"
#include "game/graphics/model/model.h"
#include "game/graphics/drawmgr.h"
#include "game/movementhandler.h"
#include "log.h"

class Biddybud : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(Biddybud, Enemy);

public:
    Biddybud(const ActorBuildInfo* buildInfo);
    virtual ~Biddybud() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    void updateModel();


    static HitboxCollider::Info collisionInfo;

    ModelWrapper* model;
    u32 behavior; 
    /* behavior chart
    0 - Stationary
    1 (temp) - left and right
    2 (temp) - up and down
    */ 
    u32 counter;
    MovementHandler movementHandler;
    bool alternater;

    DECLARE_STATE(Biddybud, Move);
    DECLARE_STATE(Biddybud, Die);
    DECLARE_STATE(Biddybud, DieSquish);
};
CREATE_STATE(Biddybud, Move);
CREATE_STATE(Biddybud, Die);
CREATE_STATE(Biddybud, DieSquish);

const Profile BiddybudProfile(&Biddybud::build, ProfileID::Biddybud);
// PROFILE_RESOURCES(ProfileID::Biddybud, Profile::LoadResourcesAt_Course, "ttwing"); // winged
PROFILE_RESOURCES(ProfileID::Biddybud, Profile::LoadResourcesAt_Course, "tenten_w");

// collider related stuff

HitboxCollider::Info Biddybud::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0f, 8.0f), HitboxCollider::HitboxShape_Rectangle, 5, 0, 0x824F, 0x20208, 0, &Enemy::collisionCallback
};

void Biddybud::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    u32 hitType = this->processCollision(hcSelf, hcOther, 0);
    if (hitType == HitType_Collide)
        this->damagePlayer(hcSelf, hcOther);
    else if (hitType == HitType_NormalJump || hitType == HitType_SpinJump)
        this->killPlayerJump(hcOther->owner, 0.0f, &Biddybud::StateID_DieSquish);
}


Biddybud::Biddybud(const ActorBuildInfo* buildInfo) 
    : Enemy(buildInfo)
    , model(nullptr)
    , behavior(0)
    , counter(0)
    , movementHandler()
    , alternater(false)
{ }

Actor* Biddybud::build(const ActorBuildInfo* buildInfo) {
    return new Biddybud(buildInfo);
}

u32 Biddybud::onCreate() {
    // this->behavior = (this->settings1 >> 0x1C & 0xF);
    // this->alternater = false;

    // this->model = ModelWrapper::create("ttwing", "biddybud", 3, 4, 3, 3, 1);
    this->model = ModelWrapper::create("tenten_w", "tenten_w", 3, 4, 3, 3, 1);
    
    this->model->playSklAnim("FlyWait");
    this->model->loopSklAnims(true);
    this->scale.x = .14;
    this->scale.y = .14;
    this->scale.z = .14;
    model->setScale(0.001);
    this->position.y -= 8;
    this->position.x += 8;

    this->hitboxCollider.init(this, &Biddybud::collisionInfo);
    this->addHitboxColliders();

    // this->movementID = (this->movementID & 0xFF); // 21-22
    // this->movementID >> 0x4 & 0xF

    u32 movementMask = this->movementHandler.getMaskForMovementType(this->settings2 & 0xFF); // nybbles 1-2?
    this->movementHandler.link(this->position, movementMask, this->movementID);

    this->doStateChange(&Biddybud::StateID_Move);
    this->updateModel();
    return this->onExecute();
}

u32 Biddybud::onExecute() {
    this->movementHandler.execute();
    this->position = this->movementHandler.position;
    this->rotation.z = this->movementHandler.rotation;

    this->states.execute();

    this->updateModel();

    return 1;
}

u32 Biddybud::onDraw() {
    DrawMgr::instance()->drawModel(this->model);
    this->model->playColorAnim("Color", 1);

    return 1;
}

void Biddybud::updateModel() {
    Mtx34 mtx;
    Vec3f modelPos = this->position;
    modelPos.y -= 8;
    mtx.makeRTIdx(this->rotation, modelPos);
    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->playColorAnim("Color", 1);
    this->model->updateAnimations();
    this->model->updateModel();
}



/** STATE: Move */

void Biddybud::beginState_Move() {
    this->counter = 0;
}

void Biddybud::executeState_Move() { }

void Biddybud::endState_Move() { }

/** STATE: Die */

void Biddybud::beginState_Die() {
    this->isDeleted = true;
    this->model->playSklAnim("BlowDown");
}

void Biddybud::executeState_Die() { }

void Biddybud::endState_Die() { }

/** STATE: DieSquish */

void Biddybud::beginState_DieSquish() {
    // this->isDeleted = true;
    this->model->playSklAnim("PressDown");
}

void Biddybud::executeState_DieSquish() { }

void Biddybud::endState_DieSquish() { }
