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

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    DECLARE_STATE(RedBlueBlock, Off);
    DECLARE_STATE(RedBlueBlock, On);

    static const PolygonCollider::Info colliderInfo;

    ModelWrapper* model;
    RectCollider collider;
    bool redBlueState; // true for blue, false for red
};

CREATE_STATE(RedBlueBlock, Off);
CREATE_STATE(RedBlueBlock, On);

REGISTER_PROFILE(RedBlueBlock, ProfileID::RedBlueBlock);
PROFILE_RESOURCES(ProfileID::RedBlueBlock, Profile::LoadResourcesAt::Course, "block_rdbl");

const PolygonCollider::Info RedBlueBlock::colliderInfo = {
    Vec2f(0.0f, 0.0f), 0.0f, 0.0f, Vec2f(-8.0f, 8.0f), Vec2f(8.0f, -8.0f), 0
};

RedBlueBlock::RedBlueBlock(const ActorBuildInfo* buildInfo)
    : MultiStateActor(buildInfo)
{ }

u32 RedBlueBlock::onCreate() {
    this->position.y -= 8.0f;
    this->position.x += 8.0f;

    this->model = ModelWrapper::create("block_rdbl", "block_rdbl", 0, 1);
    this->model->playTexPatternAnim("switch");
    this->model->texPatternAnims[0]->frameCtrl.speed = 0;

    this->redBlueState = (this->eventID1 >> 0x4 & 0xF); // nybble 1
    this->collider.init(this, colliderInfo);

    if (this->redBlueState) { // make it blue if it's supposed to be
        this->model->texPatternAnims[0]->frameCtrl.currentFrame = 1;
    }

    if (this->redBlueState == SwitchBlockState) {
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
    this->model->updateAnimations();

    this->states.execute();

    return 1;
}

u32 RedBlueBlock::onDraw() {
    if (this->states.currentState()->ID == StateID_On.ID) {
        this->model->draw();
    }

    return 1;
}

/** STATE: Off */

void RedBlueBlock::beginState_Off() {
    ColliderMgr::instance()->remove(&this->collider);
}

void RedBlueBlock::executeState_Off() {
    if (SwitchBlockState == this->redBlueState) {
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

    if (SwitchBlockState != this->redBlueState) {
        this->doStateChange(&StateID_Off);
    }
}

void RedBlueBlock::endState_On() { }
