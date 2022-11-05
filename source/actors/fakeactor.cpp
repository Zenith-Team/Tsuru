#include "game/graphics/model/modelnw.h"
#include "game/collision/collidermgr.h"
#include "game/actor/stage/multistateactor.h"
#include "game/collision/solid/rectcollider.h"
#include "game/effect/effect.h"

class FakeActor : public MultiStateActor {
    SEAD_RTTI_OVERRIDE_IMPL(FakeActor, MultiStateActor)

public:
    FakeActor(const ActorBuildInfo* buildInfo);
    virtual ~FakeActor() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void touch();
    void updateModel();

    ModelWrapper* model;
    ModelWrapper* model2;

    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    static void goalpoleCollisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    static const HitboxCollider::Info sCheckpointCollisionInfo;
    static const HitboxCollider::Info sGoalpoleCollisionInfo;
    static const HitboxCollider::Info sStarCoinCollisionInfo;

    RectCollider rectCollider;

    Vec3f effectScale;
    Vec3f effectOffset;
    Vec3f modelOffset;
    Vec3f model2Offset;

    DECLARE_STATE(FakeActor, Checkpoint);
    DECLARE_STATE(FakeActor, GoalPole);
    DECLARE_STATE(FakeActor, StarCoin);
};

CREATE_STATE(FakeActor, Checkpoint);
CREATE_STATE(FakeActor, GoalPole);
CREATE_STATE(FakeActor, StarCoin);

const Profile FakeCheckpointProfile(&FakeActor::build, ProfileID::FakeActor);
PROFILE_RESOURCES(ProfileID::FakeActor, Profile::LoadResourcesAt::Course, "middle_flag", "star_coin", "goal_set");

FakeActor::FakeActor(const ActorBuildInfo* buildInfo)
    : MultiStateActor(buildInfo)
    , rectCollider()
    , model(nullptr)
    , model2(nullptr)
    , modelOffset(0.0f, 0.0f, 0.0f)
    , model2Offset(0.0f, 0.0f, 0.0f)
    , effectOffset(0.0f, 0.0f, 0.0f)
    , effectScale(1.0f, 1.0f, 1.0f)
{ }

Actor* FakeActor::build(const ActorBuildInfo* buildInfo) {
    return new FakeActor(buildInfo);
}

u32 FakeActor::onCreate() {
    switch (this->settings1 & 0xF) { // Nybble 12
        case 0:  doStateChange(&StateID_Checkpoint); break;
        case 1:  doStateChange(&StateID_GoalPole);   break;
        case 2:  doStateChange(&StateID_StarCoin);   break;
        default: doStateChange(&StateID_Checkpoint); break;
    }
    return 1;
}

u32 FakeActor::onExecute() {
    this->updateModel();
    this->states.execute();

    return 1;
}

u32 FakeActor::onDraw() {
    if (this->model) {
        this->model->draw();
    }
    
    if (this->model2) {
        this->model2->draw();
    }

    return 1;
}

void FakeActor::updateModel() {
    if (this->model) {
        this->model->updateAnimations();
        Mtx34 mtx;
        mtx.makeRTIdx(this->rotation, this->position + this->modelOffset);
        this->model->setMtx(mtx);
        this->model->updateModel();
    }

    if (this->model2) {
        this->model2->updateAnimations();
        Mtx34 mtx;
        mtx.makeRTIdx(this->rotation, this->position + this->model2Offset);
        this->model2->setMtx(mtx);
        this->model2->updateModel();
    }
}

void FakeActor::touch() {
    Vec3f effectOrigin(this->position.x, this->position.y, 4500.0f);
    Vec3f effectPos(effectOrigin + this->effectOffset);
    Effect::spawn(RP_ObakeDoor_Disapp, &effectPos, nullptr, &this->effectScale);

    if (!(this->settings1 >> 0x1C & 0xF)) {
        this->isDeleted = true;
    }
}

void FakeActor::collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (hcOther->owner->type != StageActor::Type::Player) {
        return;
    }
    
    static_cast<FakeActor*>(hcSelf->owner)->touch();
}

/*bool FUN_02902b08(StageActor* actor);

void FakeActor::goalpoleCollisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    StageActor* actor = hcOther->owner;

    if (actor->type == 1 || actor->type == 2 && FUN_02902b08(actor)) {
        u32 unknown = 0;
        if (actor->type == 2) unknown = 2;

        actor->position.x = actor->position.x - hcSelf->_B0[unknown];
    }
}*/

/* STATE: Checkpoint */

const HitboxCollider::Info FakeActor::sCheckpointCollisionInfo = {
    Vec2f(0.0f, 24.0f), Vec2f(4.0f, 24.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0x20208, 0, &FakeActor::collisionCallback
};

void FakeActor::beginState_Checkpoint() {
    this->model = ModelWrapper::create("middle_flag", "middle_flag", 4);
    this->model->playSklAnim("wait", 0);
    this->hitboxCollider.init(this, &FakeActor::sCheckpointCollisionInfo, nullptr);
    this->addHitboxColliders();

    this->rotation.y -= 0x40000000;
    this->updateModel();
}

void FakeActor::executeState_Checkpoint() { }
void FakeActor::endState_Checkpoint() { }

/* STATE: GoalPole */

const HitboxCollider::Info FakeActor::sGoalpoleCollisionInfo = {
    Vec2f(0.0f, 76.0f), Vec2f(4.0f, 76.0f), HitboxCollider::Shape::Rectangle, 8, 0, 7, 0, 0, &FakeActor::collisionCallback
};

void FakeActor::beginState_GoalPole() {
    this->model = ModelWrapper::create("goal_set", "baseA", 1, 0, 1);
    this->model2 = ModelWrapper::create("goal_set", "goal_flag", 1, 0, 1);

    this->model2->playSklAnim("wait", 0);
    this->model2->playTexSrtAnim("wait", 0);
    this->model2Offset = Vec3f(0.0f, 80.0f, 0.0f);

    static const ShapedCollider::Info colliderInfo = {
        Vec2f(0.0f, 8.0f), 0.0f, 0.0f, Vec2f(-16.0f, 8.0f), Vec2f(16.0f, -8.0f), 0
    };

    this->rectCollider.init(this, colliderInfo);
    ColliderMgr::instance()->add(&this->rectCollider);

    this->hitboxCollider.init(this, &FakeActor::sGoalpoleCollisionInfo, nullptr);
    this->addHitboxColliders();

    this->effectOffset = Vec3f(0.0f, 20.0f, 0.0f);
    this->effectScale = Vec3f(2.25f, 2.25f, 2.25f);
    this->rotation.y -= 0x40000000;
    this->updateModel();
}

void FakeActor::executeState_GoalPole() {
    this->rectCollider.execute();
}

void FakeActor::endState_GoalPole() { }

/* STATE: StarCoin */

const HitboxCollider::Info FakeActor::sStarCoinCollisionInfo = {
    Vec2f(0.0f, -3.0f), Vec2f(12.0f, 15.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0x20208, 0, &FakeActor::collisionCallback
};

void FakeActor::beginState_StarCoin() {
    this->model = ModelWrapper::create("star_coin", "star_coinA", 0);
    this->hitboxCollider.init(this, &FakeActor::sStarCoinCollisionInfo, nullptr);
    this->addHitboxColliders();

    this->effectOffset = Vec3f(0.0f, -24.0f, 0.0f);
    this->updateModel();
}

void FakeActor::executeState_StarCoin() {
    this->rotation.y += 0x3FD27D2;
}

void FakeActor::endState_StarCoin() { }
