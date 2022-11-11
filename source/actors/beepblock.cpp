#include "game/actor/stage/multistateactor.h"
#include "game/graphics/model/modelnw.h"
#include "game/collision/solid/rectcollider.h"
#include "game/collision/collidermgr.h"
#include "game/actor/actormgr.h"
#include "game/level/levelinfo.h"
#include "game/task/taskmgr.h"
#include "game/task/coursetask.h"

class BeepBlock : public MultiStateActor {
    SEAD_RTTI_OVERRIDE_IMPL(BeepBlock, MultiStateActor);

public:
    ENUM_CLASS(Color,
        Red,
        Blue
    );

public:
    BeepBlock(const ActorBuildInfo* buildInfo);
    virtual ~BeepBlock() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    ModelWrapper* model;
    RectCollider rectCollider;
    Color::__type__ beepBlockType;

    static Color::__type__ CurrentBeepBlockState;

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
PROFILE_RESOURCES(ProfileID::BeepBlock, Profile::LoadResourcesAt::Course, "BeepBA");

const ShapedCollider::Info BeepBlock::colliderInfo = {
    Vec2f(0.0f, 0.0f), 0.0f, 0.0f, Vec2f(-8.0f, 8.0f), Vec2f(8.0f, -8.0f), 0
};

BeepBlock::Color::__type__ BeepBlock::CurrentBeepBlockState = BeepBlock::Color::Blue;

BeepBlock::BeepBlock(const ActorBuildInfo* buildInfo)
    : MultiStateActor(buildInfo)
    , model(nullptr)
    , rectCollider()
    , beepBlockType(BeepBlock::Color::Blue)
{ }

Actor* BeepBlock::build(const ActorBuildInfo* buildInfo) {
    return new BeepBlock(buildInfo);
}

u32 BeepBlock::onCreate() {
    this->rectCollider.init(this, colliderInfo);

    this->model = ModelWrapper::create("BeepBA", "BeepBA");
    this->scale = 0.1f;

    this->beepBlockType = static_cast<BeepBlock::Color::__type__>(this->eventID1 >> 0x4 & 0xF); // Nybble 1

    if (this->beepBlockType == BeepBlock::Color::Red)
        this->doStateChange(&StateID_RedDisabled);
    else
        this->doStateChange(&StateID_BlueDisabled);

    return 1;
}

u32 BeepBlock::onExecute() {
    this->model->updateAnimations();

    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->updateModel();
    this->model->setScale(this->scale);

    this->states.execute();

    return 1;
}

u32 BeepBlock::onDraw() {
    this->model->draw();

    return 1;
}

/* STATE: RedEnabled */

void BeepBlock::beginState_RedEnabled() {
    ColliderMgr::instance()->add(&this->rectCollider);

    // Don't forget to change the model here when that's done
}

void BeepBlock::executeState_RedEnabled() {
    if (CurrentBeepBlockState == BeepBlock::Color::Blue)
        this->doStateChange(&StateID_RedDisabled);

    this->rectCollider.execute();
}

void BeepBlock::endState_RedEnabled() { }

/* STATE: RedDisabled */

void BeepBlock::beginState_RedDisabled() {
    ColliderMgr::instance()->remove(&this->rectCollider);

    // Don't forget to change the model here when that's done
}

void BeepBlock::executeState_RedDisabled() {
    if (CurrentBeepBlockState == BeepBlock::Color::Red)
        this->doStateChange(&StateID_RedEnabled);
}

void BeepBlock::endState_RedDisabled() { }

/* STATE: BlueEnabled */

void BeepBlock::beginState_BlueEnabled() {
    ColliderMgr::instance()->add(&this->rectCollider);

    // Don't forget to change the model here when that's done
}

void BeepBlock::executeState_BlueEnabled() {
    if (CurrentBeepBlockState == BeepBlock::Color::Red)
        this->doStateChange(&StateID_BlueDisabled);

    this->rectCollider.execute();
}

void BeepBlock::endState_BlueEnabled() { }

/* STATE: BlueDisabled */

void BeepBlock::beginState_BlueDisabled() {
    ColliderMgr::instance()->remove(&this->rectCollider);

    // Don't forget to change the model here when that's done
}

void BeepBlock::executeState_BlueDisabled() {
    if (CurrentBeepBlockState == BeepBlock::Color::Blue)
        this->doStateChange(&StateID_BlueEnabled);
}

void BeepBlock::endState_BlueDisabled() { }
