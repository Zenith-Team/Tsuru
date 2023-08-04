#include "game/actor/stage/powerup.h"
#include "game/playermgr.h"
#include "game/effect/effect.h"
#include "game/actor/actormgr.h"
#include "tsuru/actor/blockwrapper.h"

class HammerFlower : public Powerup {
    SEAD_RTTI_OVERRIDE_IMPL(HammerFlower, Powerup);

public:
    HammerFlower(const ActorBuildInfo* buildInfo);
    virtual ~HammerFlower() { }

    u32 onCreate() override;
    u32 onExecute() override;

    void vf18C() override;
    void playBlockReleaseUpAnim() override;
    void playBlockReleaseDownAnim() override;
    void playIdleAnim() override;
    void playFloatAnim() override;
    void vf1B4() override;
    u32 vf1C4() override;
    void vf1FC() override;
};

const ActorInfo HammerFlowerActorInfo = { 0, 0, 0x20, 0x200, 0x200, 0x400, 0x400, 0 };
REGISTER_PROFILE(HammerFlower, ProfileID::HammerFlower, "HammerFlower", &HammerFlowerActorInfo, 16406);

HammerFlower::HammerFlower(const ActorBuildInfo* buildInfo)
    : Powerup(buildInfo)
{ }

u32 HammerFlower::onCreate() {
    this->_1827 = true;
    this->_1808 = 0;
    this->model = ModelWrapper::create("I_hmrflower", "I_hmrflower", 5);

    this->setupActor();
    this->spawnMethod();
    this->updateModel();

    return 1;
}

u32 HammerFlower::onExecute() {
    this->states.execute();
    this->updateModel();
    this->offscreenDelete(0);
    this->FUN_2518f94();
    this->FUN_25183ac();

    return 1;
}

void HammerFlower::vf18C() {
    this->doStateChange(&Powerup::StateID_PowerupState2);
}

void HammerFlower::playBlockReleaseUpAnim() {
    this->model->playSklAnim("out", 0);
    this->model->sklAnims[0]->frameCtrl.shouldLoop(false);
    this->_1810 = 1;
}

void HammerFlower::playBlockReleaseDownAnim() {
    this->model->playSklAnim("out3", 0);
    this->model->sklAnims[0]->frameCtrl.shouldLoop(false);
    this->_1810 = 3;
}

void HammerFlower::playIdleAnim() {
    if (this->_1810 == 4)
        return;

    this->model->playSklAnim("wait", 0);
    this->model->sklAnims[0]->frameCtrl.shouldLoop(true);
    this->_1810 = 4;
}

void HammerFlower::playFloatAnim() {
    this->model->playSklAnim("wait2", 0);
    this->model->sklAnims[0]->frameCtrl.shouldLoop(true);
    this->_1810 = 5;
}

void HammerFlower::vf1B4() {
    this->model->playSklAnim("out2", 0);
    this->model->sklAnims[0]->frameCtrl.shouldLoop(true);
    this->_1810 = 2;
}

u32 HammerFlower::vf1C4() {
    u32 local;

    if (this->FUN_25196e8(&local, PlayerBase::PowerupState::Hammer, 1) != 0)
        return this->FUN_2519580(local, this->_1830);

    return 0;
}

void HammerFlower::vf1FC() {
    this->doStateChange(&Powerup::StateID_PowerupState2);
}

class HammerBlock : public BlockWrapper {
    SEAD_RTTI_OVERRIDE_IMPL(HammerBlock, BlockWrapper);

public:
    HammerBlock(const ActorBuildInfo* buildInfo);
    virtual ~HammerBlock() { }

    u32 onCreate() override;\
    u32 onDraw() override;

    void spawnItemUp() override;
    void spawnItemDown() override;

    void spawnHammer(bool down);

    void beginState_Used() override;
};

REGISTER_PROFILE(HammerBlock, ProfileID::HammerBlock);
PROFILE_RESOURCES(ProfileID::HammerBlock, Profile::LoadResourcesAt::Course, "I_hmrflower");

HammerBlock::HammerBlock(const ActorBuildInfo* buildInfo)
    : BlockWrapper(buildInfo)
{ }

u32 HammerBlock::onCreate() {
    if (!BlockWrapper::init()) {
        return 2;
    }

    this->position.x += 8;

    if (this->stateType == BlockWrapper::StateType::UsedBlock) {
        this->doStateChange(&HammerBlock::StateID_Used);
    }

    return this->onExecute();
}

u32 HammerBlock::onDraw() {
    if (this->states.currentState()->isEqual(HammerBlock::StateID_Used)) {
        DrawMgr::instance()->drawTile(50, this->position + Vec3f(0.0f, 8.0f, 0.0f), 0, 1.0f);
    } else {
        DrawMgr::instance()->drawTile(49, this->position + Vec3f(0.0f, 8.0f, 0.0f), 0, 1.0f);
    }
    
    return 1;
}

void HammerBlock::spawnItemUp() {
    this->spawnHammer(false);
}

void HammerBlock::spawnItemDown() {
    this->spawnHammer(true);
}

void HammerBlock::spawnHammer(bool down) {
    ActorBuildInfo buildInfo = { 0 };
    buildInfo.profile = Profile::get(ProfileID::HammerFlower);
    buildInfo.position = this->position;
    buildInfo.parentID = this->id;
    buildInfo.layer = this->layer;
    if (down) {
        buildInfo.settings1 = 0x000C3000;
    } else {
        buildInfo.settings1 = 0x00082000;
    }
    ActorMgr::instance()->create(buildInfo);

    this->doStateChange(&HammerBlock::StateID_Used);
}

void HammerBlock::beginState_Used() {
    this->_1AAE = 0;
    BlockWrapper::beginState_Used();
}
