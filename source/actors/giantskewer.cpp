#include "game/actor/stage/enemy.h"
#include "game/actor/stage/playerbase.h"
#include "game/graphics/model/modelnw.h"
#include "game/sound/sound.h"
#include "game/zonerumblemgr.h"
#include "game/graphics/drawmgr.h"
#include "sead/mathcalccommon.h"

class GiantSkewer : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(GiantSkewer, Enemy);

public:
    GiantSkewer(const ActorBuildInfo* buildInfo);
    virtual ~GiantSkewer() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    bool collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    static const HitboxCollider::Info collisionInfo;

    DECLARE_STATE(GiantSkewer, Idle);
    DECLARE_STATE(GiantSkewer, PreMove);
    DECLARE_STATE(GiantSkewer, Moving);
    DECLARE_STATE(GiantSkewer, MovingEnd);
    DECLARE_STATE(GiantSkewer, Retracting);
    DECLARE_STATE(GiantSkewer, PreMoveDelay);

    ModelWrapper* model;
    f32 targetDistance, targetPosition;
    f32 premoveDistance, premovePosition;
    f32 startPosition;
    u32 idleTimer, moveEndTimer, premoveDelayTimer;
};

CREATE_STATE(GiantSkewer, Idle);
CREATE_STATE(GiantSkewer, PreMove);
CREATE_STATE(GiantSkewer, Moving);
CREATE_STATE(GiantSkewer, MovingEnd);
CREATE_STATE(GiantSkewer, Retracting);
CREATE_STATE(GiantSkewer, PreMoveDelay);

const ActorInfo GiantSkewerActorInfo = {
    Vec2i(0, 0), Vec2i(0, 0), Vec2i(240, 240), 0, 0, 0, 0, 0
};

const HitboxCollider::Info GiantSkewer::collisionInfo = {
    Vec2f(0.0f, 800.0f), Vec2f(96.0f, 1000.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0x20208, 0, &Enemy::collisionCallback
};

REGISTER_PROFILE(GiantSkewer, ProfileID::GiantSkewer, "GiantSkewer", &GiantSkewerActorInfo);
PROFILE_RESOURCES(ProfileID::GiantSkewer, Profile::LoadResourcesAt::Course,"daikonbouBig");

GiantSkewer::GiantSkewer(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , targetDistance(-(1728.0f * (f32)(this->settings1 >> 0x1C & 0xF))) // Nybble 5
    , targetPosition(0.0f)
    , premoveDistance(0.0f)
    , premovePosition(0.0f)
    , startPosition(0.0f)
    , idleTimer(0)
    , moveEndTimer(0)
    , premoveDelayTimer(0)
{ }

u32 GiantSkewer::onCreate() {
    this->startPosition = this->position.y;
    this->premovePosition = this->position.y - this->premoveDistance;

    this->hitboxCollider.init(this, &GiantSkewer::collisionInfo);
    this->addHitboxColliders();

    this->model = ModelWrapper::create("daikonbouBig", "daikonbouBig");

    this->doStateChange(&GiantSkewer::StateID_Idle);

    this->targetPosition = this->position.y + this->targetDistance;

    return this->onExecute();
}

u32 GiantSkewer::onExecute() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);

    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateModel();

    this->states.execute();

    return 1;
}

u32 GiantSkewer::onDraw() {
    this->model->draw();

    return 1;
}

bool GiantSkewer::collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    PlayerBase* player = static_cast<PlayerBase*>(hcOther->owner);

    player->vf8D4(hcSelf->owner, PlayerBase::DamageType::SingleHitBounce);

    return 1;
}

/** STATE: Idle */

void GiantSkewer::beginState_Idle() {
    this->idleTimer = 0;
}

void GiantSkewer::executeState_Idle() {
    if (this->idleTimer++ >= 180) { // Three seconds
        this->doStateChange(&GiantSkewer::StateID_PreMove);
    }
}

void GiantSkewer::endState_Idle() { }

/** STATE: PreMove */

void GiantSkewer::beginState_PreMove() {
    playSound("SE_OBJ_DAIKONBOU_L_SIGN", this->position);
}

void GiantSkewer::executeState_PreMove() {
    this->rotation.y -= 0x3000000;

    if (sead::Mathf::chase(&this->position.y, this->premovePosition, 4.0f)) {
        this->doStateChange(&GiantSkewer::StateID_Moving);
    }
}

void GiantSkewer::endState_PreMove() { }

/** STATE: PreMoveDelay */

void GiantSkewer::beginState_PreMoveDelay() {
    this->premoveDelayTimer = 0;
}

void GiantSkewer::executeState_PreMoveDelay() {
    if (this->premoveDelayTimer++ >= 60) { // One second
        this->doStateChange(&GiantSkewer::StateID_Moving);
    }
}

void GiantSkewer::endState_PreMoveDelay() { }

/** STATE: Moving */

void GiantSkewer::beginState_Moving() {
}

void GiantSkewer::executeState_Moving() {
    this->rotation.y += 0x3000000;

    if (sead::Mathf::chase(&this->position.y, this->targetPosition, 9.5f)) {
        this->doStateChange(&GiantSkewer::StateID_MovingEnd);
    }
}

void GiantSkewer::endState_Moving() {
    ZoneRumbleMgr::instance()->rumble(6);
    playSound("SE_OBJ_DAIKONBOU_L_LAND", this->position);
}

/** STATE: MovingEnd */

void GiantSkewer::beginState_MovingEnd() {
    this->moveEndTimer = 0;
}

void GiantSkewer::executeState_MovingEnd() {
    if (this->moveEndTimer++ >= 120) { // Two seconds
        this->doStateChange(&GiantSkewer::StateID_Retracting);
    }
}

void GiantSkewer::endState_MovingEnd() { }

/** STATE: Retracting */

void GiantSkewer::beginState_Retracting() { }

void GiantSkewer::executeState_Retracting() {
    this->rotation.y -= 0x3000000;

    if (sead::Mathf::chase(&this->position.y, this->startPosition, 3.0f)) {
        this->doStateChange(&GiantSkewer::StateID_Idle);
    }
}

void GiantSkewer::endState_Retracting() {
    playSound("SE_OBJ_DAIKONBOU_L_REVERT_F", this->position);
}
