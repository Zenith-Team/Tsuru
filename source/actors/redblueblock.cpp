#include "game/savemgr.h"
#include "tsuru/save/managers/tsurusavemgr.h"
#include "game/actor/stage/multistateactor.h"
#include "game/graphics/model/modelnw.h"
#include "game/collision/solid/rectcollider.h"
#include "game/collision/collidermgr.h"

#define SwitchBlockState TsuruSaveMgr::sSaveData.switchBlockBlue[SaveMgr::instance()->saveData->header.lastSessionSaveSlot]

class RedBlueBlock : public MultiStateActor {
    SEAD_RTTI_OVERRIDE_IMPL(RedBlueBlock, MultiStateActor);

public:
    RedBlueBlock(const ActorBuildInfo* buildInfo);
    virtual ~RedBlueBlock() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    DECLARE_STATE(RedBlueBlock, Off);
    DECLARE_STATE(RedBlueBlock, On);

    static const ShapedCollider::Info colliderInfo;

    ModelWrapper* model;
    RectCollider collider;
    bool red; // else blue
};

CREATE_STATE(RedBlueBlock, Off);
CREATE_STATE(RedBlueBlock, On);

const Profile RedBlueBlockProfile(&RedBlueBlock::build, ProfileID::RedBlueBlock);
PROFILE_RESOURCES(ProfileID::RedBlueBlock, Profile::LoadResourcesAt::Course, "star_coin");

const ShapedCollider::Info RedBlueBlock::colliderInfo = {
    Vec2f(0.0f, 0.0f), 0.0f, 0.0f, Vec2f(-8.0f, 8.0f), Vec2f(8.0f, -8.0f), 0
};

RedBlueBlock::RedBlueBlock(const ActorBuildInfo* buildInfo)
    : MultiStateActor(buildInfo)
{ }

Actor* RedBlueBlock::build(const ActorBuildInfo* buildInfo) {
    return new RedBlueBlock(buildInfo);
}

u32 RedBlueBlock::onCreate() {
    this->model = ModelWrapper::create("star_coin", "star_coinA");

    this->red = (this->eventID1 >> 0x4 & 0xF) == 0;
    this->collider.init(this, colliderInfo);
    
    if (SwitchBlockState != this->red) {
        this->doStateChange(&StateID_On);
    } else {
        this->doStateChange(&StateID_Off);
    }

    return this->onExecute();
}

u32 RedBlueBlock::onExecute() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);

    this->model->setMtx(mtx);
    this->model->updateModel();

    this->states.execute();

    return 1;
}

u32 RedBlueBlock::onDraw() {
    this->model->draw();

    return 1;
}

/** STATE: Off */

void RedBlueBlock::beginState_Off() {
    ColliderMgr::instance()->remove(&this->collider);
}

void RedBlueBlock::executeState_Off() {
    if (SwitchBlockState != this->red) {
        this->doStateChange(&StateID_On);
    }
}

void RedBlueBlock::endState_Off() { }

/** STATE: On */

void RedBlueBlock::beginState_On() {
    ColliderMgr::instance()->add(&this->collider);
}

void RedBlueBlock::executeState_On() {
    this->collider.execute();

    if (SwitchBlockState == this->red) {
        this->doStateChange(&StateID_Off);
    }
}

void RedBlueBlock::endState_On() { }
