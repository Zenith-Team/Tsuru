#include "game/actor/multistateactor.h"
#include "game/graphics/drawmgr.h"
#include "game/collision/collidermgr.h"
#include "game/collision/solid/rectcollider.h"
//#include "effect.h"

class FakeActor : public MultiStateActor {
public:
    FakeActor(const ActorBuildInfo* buildInfo);
    virtual ~FakeActor() {};

    static BaseActor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void touch();
    void updateModel();
    void updateModel2();

    ModelWrapper* model;
    ModelWrapper* model2;

    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    static void goalpoleCollisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    static const HitboxCollider::Info checkpointCollisionInfo;
    static const HitboxCollider::Info goalpoleCollisionInfo;
    static const HitboxCollider::Info starcoinCollisionInfo;

    RectCollider rectCollider;

    Vec3f effectScale;
    Vec3f effectOffset;
    Vec3f modeloffset;
    Vec3f model2offset;

    DECLARE_STATE(FakeActor, Checkpoint);
    DECLARE_STATE(FakeActor, GoalPole);
    DECLARE_STATE(FakeActor, StarCoin);
};

CREATE_STATE(FakeActor, Checkpoint);
CREATE_STATE(FakeActor, GoalPole);
CREATE_STATE(FakeActor, StarCoin);

const Profile FakeCheckpointProfile(&FakeActor::build, ProfileID::FakeActor, "FakeActor", nullptr, 0);
PROFILE_RESOURCES(ProfileID::FakeActor, "middle_flag", "star_coin", "goal_set");

FakeActor::FakeActor(const ActorBuildInfo* buildInfo)
    : MultiStateActor(buildInfo)
    , rectCollider()
    , model(nullptr)
    , model2(nullptr)
    , modeloffset(0.0f, 0.0f, 0.0f)
    , model2offset(0.0f, 0.0f, 0.0f)
    , effectOffset(0.0f, 0.0f, 0.0f)
    , effectScale(1.0f, 1.0f, 1.0f)
    {};

BaseActor* FakeActor::build(const ActorBuildInfo* buildInfo) {
    return new FakeActor(buildInfo);
}

u32 FakeActor::onCreate() {    
    switch (this->mSettings1 & 0xF) { // nybble 12
        case 0:  doStateChange(&StateID_Checkpoint); break;
        case 1:  doStateChange(&StateID_GoalPole);   break;
        case 2:  doStateChange(&StateID_StarCoin);   break;
        default: doStateChange(&StateID_Checkpoint); break;
    }
    return 1;
}

u32 FakeActor::onExecute() {
    this->updateModel();
    this->mStates.execute();
    //if (this->states.currentState()->isEqual(&StateID_StarCoin)) {};
    return 1;
}

u32 FakeActor::onDraw() {
    if (this->model)  DrawMgr::sInstance->drawModel(this->model);
    if (this->model2) DrawMgr::sInstance->drawModel(this->model2);
    return 1;
}

void FakeActor::updateModel() {
    if (this->model) {
        this->model->updateAnimations();
        Mtx34 mtx;
        mtx.rotateAndTranslate(this->mRotation, this->mPosition + this->modeloffset);
        this->model->setMtx(mtx);
        this->model->updateModel();
    }
    if (this->model2) {
        this->model2->updateAnimations();
        Mtx34 mtx;
        mtx.rotateAndTranslate(this->mRotation, this->mPosition + this->model2offset);
        this->model2->setMtx(mtx);
        this->model2->updateModel();
    }
}

void FakeActor::touch() {
    Vec3f effectOrigin(this->mPosition.x, this->mPosition.y, 4500.0f);
    Vec3f effectPos(effectOrigin + this->effectOffset);
    //!Effect::spawn(RP_ObakeDoor_Disapp, &effectPos, nullptr, &this->effectScale);
    if (!(this->mSettings1 >> 0x1C & 0xF)) this->mIsDeleted = true;
}

void FakeActor::collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    static_cast<FakeActor*>(hcSelf->mOwner)->touch();
}

bool FUN_02902b08(StageActor* actor);

void FakeActor::goalpoleCollisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
  StageActor* actor = hcOther->mOwner;

  if (actor->mType == 1 || actor->mType == 2 && FUN_02902b08(actor)) {
    u32 unknown = 0;

    if (actor->mType == 2) unknown = 2;

    actor->mPosition.x = actor->mPosition.x - hcSelf->_B0[unknown];
  }
}

/* STATE: Checkpoint */

const HitboxCollider::Info FakeActor::checkpointCollisionInfo = {
    Vec2f(0.0f, 24.0f), Vec2f(4.0f, 24.0f), HitboxCollider::ShapeRectangle, 5, 0, 0x824F, 0x20208, 0, &FakeActor::collisionCallback
};

void FakeActor::beginState_Checkpoint() {
    this->model = ModelWrapper::create("middle_flag", "middle_flag", 4);
    this->model->playSklAnim("wait", 0);
    this->mHitboxCollider.init(this, &FakeActor::checkpointCollisionInfo, nullptr);
    this->addHitboxColliders();

    this->mRotation.y -= 0x40000000;
    this->updateModel();
}

void FakeActor::executeState_Checkpoint() {}
void FakeActor::endState_Checkpoint() {}

/* STATE: GoalPole */

const HitboxCollider::Info FakeActor::goalpoleCollisionInfo = {
    Vec2f(0.0f, 76.0f), Vec2f(4.0f, 76.0f), HitboxCollider::ShapeRectangle, 8, 0, 7, 0, 0, &FakeActor::goalpoleCollisionCallback
};

void FakeActor::beginState_GoalPole() {
    this->model = ModelWrapper::create("goal_set", "baseA", 1, 0, 1);
    this->model2 = ModelWrapper::create("goal_set", "goal_flag", 1, 0, 1);

    this->model2->playSklAnim("wait", 0);
    this->model2->playTexSrtAnim("wait", 0);
    this->model2offset = Vec3f(0.0f, 80.0f, 0.0f);

    ShapedCollider::Info colliderInfo = {
        Vec2f(0.0f, 8.0f), 0.0f, 0.0f, Vec2f(-16.0f, 8.0f), Vec2f(16.0f, -8.0f), 0
    };
    this->rectCollider.init(this, colliderInfo);
    ColliderMgr::sInstance->add(&rectCollider);

    this->mHitboxCollider.init(this, &FakeActor::goalpoleCollisionInfo, nullptr);
    this->addHitboxColliders();

    this->effectOffset = Vec3f(0.0f, 20.0f, 0.0f);
    this->effectScale = Vec3f(2.25f, 2.25f, 2.25f);
    this->mRotation.y -= 0x40000000;
    this->updateModel();
}

void FakeActor::executeState_GoalPole() {
    this->rectCollider.execute();
}

void FakeActor::endState_GoalPole() {}

/* STATE: StarCoin */

const HitboxCollider::Info FakeActor::starcoinCollisionInfo = {
    Vec2f(0.0f, -3.0f), Vec2f(12.0f, 15.0f), HitboxCollider::ShapeRectangle, 5, 0, 0x824F, 0x20208, 0, &FakeActor::collisionCallback
};

void FakeActor::beginState_StarCoin() {
    this->model = ModelWrapper::create("star_coin", "star_coinA", 0);
    this->mHitboxCollider.init(this, &FakeActor::starcoinCollisionInfo, nullptr);
    this->addHitboxColliders();

    this->effectOffset = Vec3f(0.0f, -24.0f, 0.0f);
    this->updateModel();
}

void FakeActor::executeState_StarCoin() {
    this->mRotation.y += 0x3FD27D2;
}

void FakeActor::endState_StarCoin() {}
