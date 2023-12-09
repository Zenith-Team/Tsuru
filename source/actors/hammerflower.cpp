#include "game/actor/stage/powerup.h"
#include "game/playermgr.h"
#include "game/effect/effect.h"

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

const ActorInfo HammerFlowerActorInfo = { Vec2i(8, -16), Vec2i(0x0, 0x10), Vec2i(0x20, 0x20), 0x200, 0x200, 0x400, 0x400, 0 };
REGISTER_PROFILE(HammerFlower, ProfileID::HammerFlower, "HammerFlower", &HammerFlowerActorInfo, 0x4016);
PROFILE_RESOURCES(ProfileID::HammerFlower, Profile::LoadResourcesAt::Course, "I_hmrflower");

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
