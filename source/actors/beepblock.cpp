#include "game/actor/stage/multistateactor.h"
#include "game/graphics/model/model.h"
#include "game/graphics/drawmgr.h"
#include "game/collision/solid/rectcollider.h"
#include "game/collision/collidermgr.h"
#include "game/actor/actormgr.h"
#include "game/level/levelinfo.h"
#include "game/task/taskmgr.h"
#include "game/task/coursetask.h"

class BeepBlock : public MultiStateActor {
    SEAD_RTTI_OVERRIDE_IMPL(BeepBlock, MultiStateActor)

public:
    enum BeepBlockColor {
        BeepBlockColor_Red = 0,
        BeepBlockColor_Blue = 1
    };

public:
    BeepBlock(const ActorBuildInfo* buildInfo);
    virtual ~BeepBlock() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    ModelWrapper* model;
    RectCollider rectCollider;
    BeepBlockColor beepBlockType;

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

const Profile BeepBlockProfile(&BeepBlock::build, ProfileID::BeepBlock);

const ShapedCollider::Info BeepBlock::colliderInfo = {
    Vec2f(0.0f, 0.0f), 0.0f, 0.0f, Vec2f(-16.0f, 8.0f), Vec2f(16.0f, -8.0f), 0
};

BeepBlock::BeepBlockColor BeepBlock::CurrentBeepBlockState = BeepBlock::BeepBlockColor_Blue;

BeepBlock::BeepBlock(const ActorBuildInfo* buildInfo)
    : MultiStateActor(buildInfo)
    , model(nullptr)
    , rectCollider()
    , beepBlockType(BeepBlockColor_Blue)
{ }

Actor* BeepBlock::build(const ActorBuildInfo* buildInfo) {
    return new BeepBlock(buildInfo);
}

u32 BeepBlock::onCreate() {
    this->rectCollider.init(this, colliderInfo);

    this->model = ModelWrapper::create("star_coin", "star_coinA");

    this->beepBlockType = static_cast<BeepBlockColor>(this->eventID1 >> 0x4 & 0xF); // Nybble 1

    if (this->beepBlockType == BeepBlockColor_Red)
        this->doStateChange(&StateID_RedDisabled);
    else
        this->doStateChange(&StateID_BlueDisabled);

    return 1;
}

u32 BeepBlock::onExecute() {
    this->model->updateAnimations();

    Mtx34 mtx;
    mtx.rotateAndTranslate(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->updateModel();

    this->states.execute();

    return 1;
}

u32 BeepBlock::onDraw() {
    DrawMgr::instance()->drawModel(this->model);

    return 1;
}

/* STATE: RedEnabled */

void BeepBlock::beginState_RedEnabled() {
    ColliderMgr::instance()->add(&this->rectCollider);

    // Don't forget to change the model here when that's done :)
}

void BeepBlock::executeState_RedEnabled() {
    if (CurrentBeepBlockState == BeepBlockColor_Blue)
        this->doStateChange(&StateID_RedDisabled);

    this->rectCollider.execute();
}

void BeepBlock::endState_RedEnabled() { }

/* STATE: RedDisabled */

void BeepBlock::beginState_RedDisabled() {
    ColliderMgr::instance()->remove(&this->rectCollider);

    // Don't forget to change the model here when that's done :)
}

void BeepBlock::executeState_RedDisabled() {
    if (CurrentBeepBlockState == BeepBlockColor_Red)
        this->doStateChange(&StateID_RedEnabled);
}

void BeepBlock::endState_RedDisabled() { }

/* STATE: BlueEnabled */

void BeepBlock::beginState_BlueEnabled() {
    ColliderMgr::instance()->add(&this->rectCollider);

    // Don't forget to change the model here when that's done :)
}

void BeepBlock::executeState_BlueEnabled() {
    if (CurrentBeepBlockState == BeepBlockColor_Red)
        this->doStateChange(&StateID_BlueDisabled);

    this->rectCollider.execute();
}

void BeepBlock::endState_BlueEnabled() { }

/* STATE: BlueDisabled */

void BeepBlock::beginState_BlueDisabled() {
    ColliderMgr::instance()->remove(&this->rectCollider);

    // Don't forget to change the model here when that's done :)
}

void BeepBlock::executeState_BlueDisabled() {
    if (CurrentBeepBlockState == BeepBlockColor_Blue)
        this->doStateChange(&StateID_BlueEnabled);
}

void BeepBlock::endState_BlueDisabled() { }
