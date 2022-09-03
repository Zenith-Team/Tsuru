#include "game/actor/stage/multistateactor.h"
#include "game/graphics/model/modelnw.h"
#include "game/movementhandler.h"
#include "game/eventmgr.h"
#include "game/effect/effect.h"
#include "game/collision/collidermgr.h"
#include "game/collision/solid/rectcollider.h"
#include "game/graphics/model/animation.h"
#include "log.h"

class SwitchBlock : public MultiStateActor {
    SEAD_RTTI_OVERRIDE_IMPL(SwitchBlock, MultiStateActor);

public:
    SwitchBlock(const ActorBuildInfo* buildInfo);
    virtual ~SwitchBlock() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void switchState();
    void updateModel();

    static HitboxCollider::Info collisionInfo;
    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    
    ModelWrapper* model;
    MovementHandler movementHandler;
    Vec3f effectScale;
    Vec3f effectOffset;
    RectCollider rectCollider;
    bool oneTimeUse;
    bool isInactive;
    bool initialState; // false for red, true for blue
    u32 currentState;
    u32 eventR;
    u32 eventB;
    u32 delayCounter;
    u32 delay;

    enum SwitchBlockState {
        SwitchBlock_Red = 0,
        SwitchBlock_Blue = 1,
        SwitchBlock_Inactive = 2,
    };

    DECLARE_STATE(SwitchBlock, Red);
    DECLARE_STATE(SwitchBlock, Blue);
    DECLARE_STATE(SwitchBlock, Inactive);
};

CREATE_STATE(SwitchBlock, Red);
CREATE_STATE(SwitchBlock, Blue);
CREATE_STATE(SwitchBlock, Inactive);

const Profile SwitchBlockProfile(&SwitchBlock::build, ProfileID::SwitchBlock);
PROFILE_RESOURCES(ProfileID::SwitchBlock, Profile::LoadResourcesAt_Course, "block_stch");

HitboxCollider::Info SwitchBlock::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0f, 12.0f), HitboxCollider::HitboxShape_Rectangle, 5, 0, 0x824F, 0xFFFFFFFF, 0, &SwitchBlock::collisionCallback
};

void SwitchBlock::collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    static_cast<SwitchBlock*>(hcSelf->owner)->switchState();
}

SwitchBlock::SwitchBlock(const ActorBuildInfo* buildInfo)
    : MultiStateActor(buildInfo)
    , rectCollider()
    , model(nullptr)
    , effectOffset(0.0f, 0.0f, 0.0f)
    , effectScale(1.0f, 1.0f, 1.0f)
    , oneTimeUse(false)
    , isInactive(false)
    , initialState(false)
    , currentState(0)
    , delayCounter(0)
    , delay(0)
{ }

Actor* SwitchBlock::build(const ActorBuildInfo* buildInfo) {
    return new SwitchBlock(buildInfo);
}

u32 SwitchBlock::onCreate() {
    this->initialState = (this->settings1 >> 0x1C & 0xF); // nybble 5
    this->oneTimeUse = (this->settings1 >> 0x18 & 0xF); // nybble 6
    this->eventR = (this->settings1 >> 0x10 & 0xFF) -1; // nybble 7-8
    this->eventB = (this->settings1 >> 0x8 & 0xFF) -1; // nybble 9-10
    this->delay = (this->settings1 >> 0x4 & 0xF) * 60; // nybble 11

    if (this->delay == 0) {
        this->delay = 10;
    }

    this->model = ModelWrapper::create("block_stch", "block_stch", 2, 1);
    this->model->playTexPatternAnim("switch", 0);
    this->model->texPatternAnims[0]->frameCtrl.currentFrame = this->initialState;
    this->currentState = this->initialState;
    this->model->texPatternAnims[0]->frameCtrl.speed = 0.0;
    this->position.x += 8;
    this->position.y -= 8;
    this->updateModel();

    static const ShapedCollider::Info colliderInfo = {
        Vec2f(0.0f, 0.0f), 0.0f, 0.0f, Vec2f(-8.0f, 8.0f), Vec2f(8.0f, -8.0f), 0
    };

    this->rectCollider.init(this, colliderInfo);
    ColliderMgr::instance()->add(&this->rectCollider);

    this->hitboxCollider.init(this, &SwitchBlock::collisionInfo, nullptr);
    this->addHitboxColliders();
    
    u32 movementMask = this->movementHandler.getMaskForMovementType(this->settings2 & 0xFF); // nybble 20
    this->movementHandler.link(this->position, movementMask, this->movementID); // nybble 21-22

    switch (this->initialState) {
        case SwitchBlock_Red: doStateChange(&StateID_Red); break;
        case SwitchBlock_Blue: doStateChange(&StateID_Blue); break;
        default: doStateChange(&StateID_Red); break;
    }

    return 1;
}

u32 SwitchBlock::onExecute() {
    this->states.execute();

    if (this->isInactive) {
        doStateChange(&SwitchBlock::StateID_Inactive);
    }

    else {
        this->movementHandler.execute();
        this->position = this->movementHandler.position;
    }

    this->updateModel();
    this->delayCounter++;

    return 1;
}

u32 SwitchBlock::onDraw() {
    this->model->draw();

    return 1;
}

void SwitchBlock::updateModel() {
    Mtx34 mtx;
    Vec3f modelPos = this->position;
    mtx.makeRTIdx(this->rotation, modelPos);

    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateAnimations();
    this->model->updateModel();
}

void SwitchBlock::switchState() {
    if (this->delayCounter > this->delay) {
        this->delayCounter = 0;
        if (!isInactive) {
            if (this->currentState == SwitchBlock_Red) {
                EventMgr::instance()->set(eventR, 0, false);
                EventMgr::instance()->set(eventB, 0, true);
                Vec3f effectOrigin(this->position.x, this->position.y, 4500.0f);
                Vec3f effectPos(effectOrigin + this->effectOffset);
                Effect::spawn(RP_Jugemu_CloudDisapp, &effectPos, nullptr, &this->effectScale);                
                if (this->oneTimeUse)
                    doStateChange(&StateID_Inactive);
                else
                    doStateChange(&StateID_Blue);
            } else if (this->currentState == SwitchBlock_Blue) {
                EventMgr::instance()->set(eventB, 0, false);
                EventMgr::instance()->set(eventR, 0, true);
                Vec3f effectOrigin(this->position.x, this->position.y, 4500.0f);
                Vec3f effectPos(effectOrigin + this->effectOffset);
                Effect::spawn(RP_Jugemu_CloudDisapp, &effectPos, nullptr, &this->effectScale);
                if (this->oneTimeUse)
                    doStateChange(&StateID_Inactive);
                else
                    doStateChange(&StateID_Red);
            }
        }
    }
}

/** STATE:Red */

void SwitchBlock::beginState_Red() {
    this->currentState = SwitchBlock_Red;
    this->model->texPatternAnims[0]->frameCtrl.currentFrame = this->currentState;
}

void SwitchBlock::executeState_Red() { }

void SwitchBlock::endState_Red() { }

/** STATE: Blue */

void SwitchBlock::beginState_Blue() {
    this->currentState = SwitchBlock_Blue;
    this->model->texPatternAnims[0]->frameCtrl.currentFrame = this->currentState;
}

void SwitchBlock::executeState_Blue() { }

void SwitchBlock::endState_Blue() { }

/** STATE: Inactive */

void SwitchBlock::beginState_Inactive() {
    this->isInactive = true;
    this->currentState = SwitchBlock_Inactive;
    this->model->texPatternAnims[0]->frameCtrl.currentFrame = 3;
}

void SwitchBlock::executeState_Inactive() { }

void SwitchBlock::endState_Inactive() { }
