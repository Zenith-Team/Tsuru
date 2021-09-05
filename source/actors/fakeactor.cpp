#include <game/graphics/drawmgr.h>
#include <game/collision/collidermgr.h>
#include <game/actor/stage/multistateactor.h>
#include <game/collision/solid/rectcollider.h>
#include <game/effect/effect.h>

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
    void updateModel2();

    ModelWrapper* mModel;
    ModelWrapper* mModel2;

    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    static void goalpoleCollisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    static const HitboxCollider::Info sCheckpointCollisionInfo;
    static const HitboxCollider::Info sGoalpoleCollisionInfo;
    static const HitboxCollider::Info sStarcoinCollisionInfo;

    RectCollider mRectCollider;

    Vec3f mEffectScale;
    Vec3f mEffectOffset;
    Vec3f mModelOffset;
    Vec3f mModel2Offset;

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
    , mRectCollider()
    , mModel(nullptr)
    , mModel2(nullptr)
    , mModelOffset(0.0f, 0.0f, 0.0f)
    , mModel2Offset(0.0f, 0.0f, 0.0f)
    , mEffectOffset(0.0f, 0.0f, 0.0f)
    , mEffectScale(1.0f, 1.0f, 1.0f)
{ }

Actor* FakeActor::build(const ActorBuildInfo* buildInfo) {
    return new FakeActor(buildInfo);
}

u32 FakeActor::onCreate() {    
    switch (this->mSettings1 & 0xF) { // Nybble 12
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
    //if (this->mStates.currentState()->isEqual(&StateID_StarCoin)) {};
    return 1;
}

u32 FakeActor::onDraw() {
    if (this->mModel)  DrawMgr::instance()->drawModel(this->mModel);
    if (this->mModel2) DrawMgr::instance()->drawModel(this->mModel2);
    return 1;
}

void FakeActor::updateModel() {
    if (this->mModel) {
        this->mModel->updateAnimations();
        Mtx34 mtx;
        mtx.rotateAndTranslate(this->mRotation, this->mPosition + this->mModelOffset);
        this->mModel->setMtx(mtx);
        this->mModel->updateModel();
    }

    if (this->mModel2) {
        this->mModel2->updateAnimations();
        Mtx34 mtx;
        mtx.rotateAndTranslate(this->mRotation, this->mPosition + this->mModel2Offset);
        this->mModel2->setMtx(mtx);
        this->mModel2->updateModel();
    }
}

void FakeActor::touch() {
    Vec3f effectOrigin(this->mPosition.x, this->mPosition.y, 4500.0f);
    Vec3f effectPos(effectOrigin + this->mEffectOffset);
    Effect::spawn(RP_ObakeDoor_Disapp, &effectPos, nullptr, &this->mEffectScale);
    if (!(this->mSettings1 >> 0x1C & 0xF)) this->mIsDeleted = true;
}

void FakeActor::collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    static_cast<FakeActor*>(hcSelf->mOwner)->touch();
}

/*bool FUN_02902b08(StageActor* actor);

void FakeActor::goalpoleCollisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
  StageActor* actor = hcOther->mOwner;

  if (actor->type == 1 || actor->type == 2 && FUN_02902b08(actor)) {
    u32 unknown = 0;

    if (actor->type == 2) unknown = 2;

    actor->mPosition.x = actor->mPosition.x - hcSelf->_B0[unknown];
  }
}*/

/* STATE: Checkpoint */

const HitboxCollider::Info FakeActor::sCheckpointCollisionInfo = {
    Vec2f(0.0f, 24.0f), Vec2f(4.0f, 24.0f), HitboxCollider::ShapeRectangle, 5, 0, 0x824F, 0x20208, 0, &FakeActor::collisionCallback
};

void FakeActor::beginState_Checkpoint() {
    this->mModel = ModelWrapper::create("middle_flag", "middle_flag", 4);
    this->mModel->playSklAnim("wait", 0);
    this->mHitboxCollider.init(this, &FakeActor::sCheckpointCollisionInfo, nullptr);
    this->addHitboxColliders();

    this->mRotation.y -= 0x40000000;
    this->updateModel();
}

void FakeActor::executeState_Checkpoint() {}
void FakeActor::endState_Checkpoint() {}

/* STATE: GoalPole */

const HitboxCollider::Info FakeActor::sGoalpoleCollisionInfo = {
    Vec2f(0.0f, 76.0f), Vec2f(4.0f, 76.0f), HitboxCollider::ShapeRectangle, 8, 0, 7, 0, 0, &FakeActor::collisionCallback
};

void FakeActor::beginState_GoalPole() {
    this->mModel = ModelWrapper::create("goal_set", "baseA", 1, 0, 1);
    this->mModel2 = ModelWrapper::create("goal_set", "goal_flag", 1, 0, 1);

    this->mModel2->playSklAnim("wait", 0);
    this->mModel2->playTexSrtAnim("wait", 0);
    this->mModel2Offset = Vec3f(0.0f, 80.0f, 0.0f);

    ShapedCollider::Info colliderInfo = {
        Vec2f(0.0f, 8.0f), 0.0f, 0.0f, Vec2f(-16.0f, 8.0f), Vec2f(16.0f, -8.0f), 0
    };

    this->mRectCollider.init(this, colliderInfo);
    ColliderMgr::instance()->add(&mRectCollider);

    this->mHitboxCollider.init(this, &FakeActor::sGoalpoleCollisionInfo, nullptr);
    this->addHitboxColliders();

    this->mEffectOffset = Vec3f(0.0f, 20.0f, 0.0f);
    this->mEffectScale = Vec3f(2.25f, 2.25f, 2.25f);
    this->mRotation.y -= 0x40000000;
    this->updateModel();
}

void FakeActor::executeState_GoalPole() {
    this->mRectCollider.execute();
}

void FakeActor::endState_GoalPole() {}

/* STATE: StarCoin */

const HitboxCollider::Info FakeActor::sStarcoinCollisionInfo = {
    Vec2f(0.0f, -3.0f), Vec2f(12.0f, 15.0f), HitboxCollider::ShapeRectangle, 5, 0, 0x824F, 0x20208, 0, &FakeActor::collisionCallback
};

void FakeActor::beginState_StarCoin() {
    this->mModel = ModelWrapper::create("star_coin", "star_coinA", 0);
    this->mHitboxCollider.init(this, &FakeActor::sStarcoinCollisionInfo, nullptr);
    this->addHitboxColliders();

    this->mEffectOffset = Vec3f(0.0f, -24.0f, 0.0f);
    this->updateModel();
}

void FakeActor::executeState_StarCoin() {
    this->mRotation.y += 0x3FD27D2;
}

void FakeActor::endState_StarCoin() {}
