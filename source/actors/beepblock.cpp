#include <game/actor/stage/multistateactor.h>
#include <game/graphics/model/model.h>
#include <game/graphics/drawmgr.h>
#include <game/collision/solid/rectcollider.h>
#include <game/collision/collidermgr.h>
#include <game/actor/actormgr.h>

class BeepBlock : public MultiStateActor {
public:
    enum BeepBlockColor {
        BeepBlockColorRed = 0,
        BeepBlockColorBlue = 1
    };

public:
    BeepBlock(const ActorBuildInfo* buildInfo);
    virtual ~BeepBlock() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    ModelWrapper* mModel;
    RectCollider mRectCollider;
    BeepBlockColor mBeepBlockType;

    static BeepBlockColor CurrentBeepBlockState;
    
    static const ShapedCollider::Info colliderInfo;

    DECLARE_STATE(BeepBlock, RedEnabled);
    DECLARE_STATE(BeepBlock, RedDisabled);
    DECLARE_STATE(BeepBlock, BlueEnabled);
    DECLARE_STATE(BeepBlock, BlueDisabled);
};

CREATE_STATE(BeepBlock, RedEnabled);
CREATE_STATE(BeepBlock, RedDisabled);
CREATE_STATE(BeepBlock, BlueEnabled);
CREATE_STATE(BeepBlock, BlueDisabled);

const Profile BeepBlockProfile(&BeepBlock::build, ProfileID::BeepBlock, "BeepBlock", nullptr, 0);

const ShapedCollider::Info BeepBlock::colliderInfo = {
    Vec2f(0.0f, 0.0f), 0.0f, 0.0f, Vec2f(-16.0f, 8.0f), Vec2f(16.0f, -8.0f), 0
};

BeepBlock::BeepBlockColor BeepBlock::CurrentBeepBlockState = BeepBlock::BeepBlockColorBlue;

BeepBlock::BeepBlock(const ActorBuildInfo* buildInfo)
    : MultiStateActor(buildInfo)
    , mModel(nullptr)
    , mRectCollider()
    , mBeepBlockType(BeepBlockColorBlue)
{ }

Actor* BeepBlock::build(const ActorBuildInfo* buildInfo) {
    return new BeepBlock(buildInfo);
}

u32 BeepBlock::onCreate() {
    this->mRectCollider.init(this, colliderInfo);

    this->mModel = ModelWrapper::create("star_coin", "star_coinA");

    this->mBeepBlockType = static_cast<BeepBlockColor>(this->mSettings1 >> 0x1C);

    if (this->mBeepBlockType == BeepBlockColorRed)
        this->doStateChange(&StateID_RedDisabled);
    else
        this->doStateChange(&StateID_BlueDisabled);

    return 1;
}

u32 BeepBlock::onExecute() {
    this->mModel->updateAnimations();
    
    Mtx34 mtx;
    mtx.rotateAndTranslate(this->mRotation, this->mPosition);
    this->mModel->setMtx(mtx);
    this->mModel->updateModel();

    this->mStates.execute();

    return 1;
}

u32 BeepBlock::onDraw() {
    DrawMgr::instance()->drawModel(this->mModel);

    return 1;
}

/* STATE: RedEnabled */

void BeepBlock::beginState_RedEnabled() {
    ColliderMgr::instance()->add(&this->mRectCollider);

    // Don't forget to change the model here when that's done :)
}

void BeepBlock::executeState_RedEnabled() {
    if (CurrentBeepBlockState == BeepBlockColorBlue)
        this->doStateChange(&StateID_RedDisabled);
    
    this->mRectCollider.execute();
}

void BeepBlock::endState_RedEnabled() { }

/* STATE: RedDisabled */

void BeepBlock::beginState_RedDisabled() {
    ColliderMgr::instance()->remove(&this->mRectCollider);

    // Don't forget to change the model here when that's done :)
}

void BeepBlock::executeState_RedDisabled() {
    if (CurrentBeepBlockState == BeepBlockColorRed)
        this->doStateChange(&StateID_RedEnabled);
}

void BeepBlock::endState_RedDisabled() { }

/* STATE: BlueEnabled */

void BeepBlock::beginState_BlueEnabled() {
    ColliderMgr::instance()->add(&this->mRectCollider);

    // Don't forget to change the model here when that's done :)
}

void BeepBlock::executeState_BlueEnabled() {
    if (CurrentBeepBlockState == BeepBlockColorRed)
        this->doStateChange(&StateID_BlueDisabled);
    
    this->mRectCollider.execute();
}

void BeepBlock::endState_BlueEnabled() { }

/* STATE: BlueDisabled */

void BeepBlock::beginState_BlueDisabled() {
    ColliderMgr::instance()->remove(&this->mRectCollider);

    // Don't forget to change the model here when that's done :)
}

void BeepBlock::executeState_BlueDisabled() {
    if (CurrentBeepBlockState == BeepBlockColorBlue)
        this->doStateChange(&StateID_BlueEnabled);
}

void BeepBlock::endState_BlueDisabled() { }
